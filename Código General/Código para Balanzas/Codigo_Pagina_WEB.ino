#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "Datos_De_Red.h"
#include "html.h"

#include "HX711.h"

const int LOADCELL_DOUT_PIN = 22;
const int LOADCELL_SCK_PIN = 23;

const int LOADCELL_DOUT_PIN2 = 19;
const int LOADCELL_SCK_PIN2 = 4;

HX711 scale1;
HX711 scale2;

float peso1;
float peso2;

bool datoRecibidopagina = false;
bool datoRecibidoserial = false;

int periodo = 500;
unsigned long TiempoAhora = 0;
char estado;
bool check = false;
bool check2;
//--------------------------------------------------------------------------
const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034
unsigned long previousMillis = 0;
const long interval = 50;
long duration;
float distanceCm;
//--------------------------------------------------------------------------

int CantidadValores = 0;
int cantidaddeLiquidoWEB1;
int cantidaddeLiquidoWEB2;
bool flagWEB;

// Configuración de UART
const int uartTxPin = 17; // Pin de transmisión UART
const int uartRxPin = 16; // Pin de recepción UART

const int uartBaudRate = 9600; // Velocidad de baudios UART

WebServer server(80);

// Pin led
#define LED_BUILTIN 2

// Declaración de la variable global, deben ser diferente nombre a las capturadas por el serial...
int volumenRecipiente = 0;
float cantidaddeLiquido1 = 0;
float cantidaddeLiquido2 = 0;

void handleRoot() {
  String page = String(html_code);
  page.replace("%VOLUMEN_RECIP%", "");
  page.replace("%CANTIDAD_LIQUIDO_1%", "");
  page.replace("%CANTIDAD_LIQUIDO_2%", "");
  server.send(200, "text/html", page);
}

void handleForm() {

  String page = String(html_code);
  page.replace("%VOLUMEN_RECIP%", server.arg("Volumen_del_recipiente"));
  page.replace("%CANTIDAD_LIQUIDO_1%", server.arg("Cantidad_liquido_1"));
  page.replace("%CANTIDAD_LIQUIDO_2%", server.arg("Cantidad_liquido_2"));
  server.send(200, "text/html", page);

  if (datoRecibidoserial == false) {
    String volumendelRecipiente = server.arg("Volumen_del_recipiente");
    String cantidadLiquido1 = server.arg("Cantidad_liquido_1");
    String cantidadLiquido2 = server.arg("Cantidad_liquido_2");

    Serial.println("Volumen del recipiente: " + volumendelRecipiente);
    Serial.println("Cantidad líquido 1: " + cantidadLiquido1);
    Serial.println("Cantidad líquido 2: " + cantidadLiquido2);

    //estas lineas son para capturar el dato y almacenarlo en una variable para poder usarlo.
    volumenRecipiente = server.arg("Volumen_del_recipiente").toInt();
    cantidaddeLiquido1 = server.arg("Cantidad_liquido_1").toInt();
    cantidaddeLiquido2 = server.arg("Cantidad_liquido_2").toInt();

    cantidaddeLiquidoWEB1 = cantidaddeLiquido1;
    cantidaddeLiquidoWEB2 = cantidaddeLiquido2;
    datoRecibidopagina = true;
  }
}

void setup() {
  Serial.begin(115200);

  //Define entradas y salidas
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/procesar", handleForm);

  server.begin();

  Serial.println("Server started");

  //----------------------------------------------------------------------
  scale1.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale1.set_scale(200.6420);  ///// Para balanza de Marron

  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  scale2.set_scale(-195.993);  ///// Para balanza de Negra

  scale1.tare();
  scale2.tare();
  //----------------------------------------------------------------------

  Serial2.begin(uartBaudRate, SERIAL_8N1, uartRxPin, uartTxPin); // Inicializar UART

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();

  server.handleClient();

  TiempoAhora = millis();
  peso1 = scale1.get_units(5);
  Serial.print("Balanza Marron (peso1): ");
  Serial.print(peso1);
  Serial.print(" gramos");

  peso2 = scale2.get_units(5);
  Serial.print("            Balanza Negra (peso2): ");
  Serial.print(peso2);
  Serial.println(" gramos");

  TiempoAhora = millis();

  //-----------------Recibir Valores pedidos por el usuario a traves del Serial y enviar un flag a serial2--------------//
  if (!datoRecibidoserial && datoRecibidopagina == false) {  // Recibido==false
    // Check if data is available to read from the Serial Monitor

    if (Serial.available() > 0) {
      if (CantidadValores == 0) {
        cantidaddeLiquido1 = Serial.parseInt();
        Serial.read();
        Serial.print("Valor 1 Recibido: ");
        Serial.println(cantidaddeLiquido1);
        CantidadValores = 1;
      }
      else if (CantidadValores == 1) {
        cantidaddeLiquido2 = Serial.parseInt();
        Serial.read();
        Serial.print("Valor 2 Recibido: ");
        Serial.println(cantidaddeLiquido2);
        //-----------------------Enviar Datos ingresados a traves del serial2------------------------//
        int OK = 10;

        Serial2.print(OK);
        Serial.println("Se enviaron datos por el Serial");
        Serial.println(OK);

        //-----------------------------------------------//
        // Set the flag to indicate that a value has been received
        datoRecibidoserial = true;
      }
    }
  }
  if (datoRecibidopagina == true && flagWEB == false)
  {
    int OK = 10;
    Serial2.print(OK);
    flagWEB = true;

    Serial.println(cantidaddeLiquido1);

    Serial.println(cantidaddeLiquido2);
  }
  if (datoRecibidoserial == true || datoRecibidopagina == true)
  {
    if (peso2 <= -cantidaddeLiquido1 && check == false) {
      check = true;
      Serial.print("Peso 1 Pedido = ");
      estado = '0';
      Serial2.println(estado);

      Serial.println(cantidaddeLiquido1);
      Serial.println("Condicion Cumplida peso1");
    }
    if (peso1 <= -cantidaddeLiquido2 && check == true) {
      check = false;
      estado = '1';
      Serial2.println(estado);
      Serial.print("Peso 2 Pedido = ");
      Serial.println(cantidaddeLiquido2);
      Serial.println("Condicion Cumplida peso2");
    }
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);

      // Calculate the distance
      distanceCm = duration * SOUND_SPEED / 2; //

      if (distanceCm <= 10) {
        estado = '4';
      }
    }
  }
}
