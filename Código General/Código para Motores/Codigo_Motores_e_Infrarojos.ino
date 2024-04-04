#include <HardwareSerial.h>
//---------------Motor Nema 17-------------------------------------
#include <Wire.h>
#include <AccelStepper.h>
#define dirPin1 18
#define stepPin1 19
#define dirPin2 33
#define stepPin2 32

#define motorInterfaceType 1
AccelStepper stepper1 = AccelStepper(motorInterfaceType, stepPin1, dirPin1);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2 = AccelStepper(motorInterfaceType, stepPin2, dirPin2);

//-----------Motor DC-----------------------------------------
int A1A = 15;
int A1B = 4;
//----------------------------------------------------

const int uartRxPin = 16;       // Pin de recepción UART
const int uartTxPin = 17;       // Pin de recepción UART
const int uartBaudRate = 9600;  // Velocidad de baudios UART

//--------------------------------------------------------------------------
int ValorRecib;         // Declare a variable to store the received value
bool Recibido = false;  // Flag to track if a value has been received
//--------------------------------------------------------------------------

const int BUTTON_PIN = 21;//pulsador
bool Puerta_Abierta = true;

float peso;
char estado = 49;
int motorprendido;

float Liq_A;
float Liq_B;
bool Sensor1;
bool Sensor2;

bool Ir1 = false;
bool Ir2 = false;

bool Etapa1 = true;
bool Etapa2;
bool Etapa3;
bool Etapa4;
bool Etapa5;
bool Etapa6;
bool Etapa7;
bool Etapa8;
bool Etapa9;
bool Etapa0;
bool Etapa10 = true;
bool Etapa11 = true;
bool Etapa12 = true;
bool Etapa13 = true;
bool Etapa14 = true;

bool Plataforma;
bool BombaA;
bool BombaB;
bool Puerta;


////////////////////Debounce Pulsador/////////////////////////
int Pulsador = LOW;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime =  0;
unsigned long debounceDelay = 50;
////////////////////Debounce Pulsador/////////////////////////

//sensor infrarrojo
int IR2 = 26;  //Entrada digital conectada al sensor infrarrojo
int IR1 = 25;  //Entrada digital conectada al sensor infrarrojo

void setup() {
  Serial.begin(115200);
  Serial2.begin(uartBaudRate, SERIAL_8N1, uartRxPin, uartTxPin);
  Serial.println("Colocar Recipiente frente al Sensor 1");

  //sensores infrarrojos
  pinMode(IR1, INPUT);  //Sensor infrarrojo como entrada
  pinMode(IR2, INPUT);  //Sensor infrarrojo como entrada

  //Motor DC
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() {

  if (!Recibido) {  // Recibido==false
    // Check if data is available to read from the Serial Monitor

    if (Serial2.available() > 0) {
      String ValorRecibido = Serial2.readStringUntil('\n');
      int ValorGuardado = ValorRecibido.toInt();

      if (ValorGuardado == 10) {
        Serial.print("Valor Recibido por Serial2: ");
        Serial.println("OK");
        Recibido = true;
      }
    }
  }

  bool Ir1 = digitalRead(IR1);   //leemos el valor del sensor infrarrojo
  bool Ir2 = digitalRead(IR2);  //leemos el valor del sensor infrarrojo
  //el valor del infrarrojo sin detectar nada es un 1
  //
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        Pulsador = LOW;
      }
      else {
        Pulsador = HIGH;
      }
    }
  }
  lastButtonState = reading;

  if (Pulsador == HIGH) {

    Puerta = true; // La puerta se cerró

    if (Ir1 == false && Etapa1 == true && Recibido == true) {
      Plataforma = true;
      Etapa1 = false;
      Etapa2 = true;
      delay(2000);
      Serial.println(" ");
      Serial.println("Plataforma Encendida: Transportando");
    }

    if (Plataforma == true && (Etapa2 == true || Etapa8 == true)) {
      digitalWrite(A1A, LOW);
      digitalWrite(A1B, HIGH);
    }

    if (Ir2 == false && Etapa2 == true) {
      Plataforma = false;
      Etapa2 = false;
      Etapa3 = true;
      Serial.println("Plataforma Apagada... Recipiente en posicion");
    }

    if (Plataforma == false && (Etapa3 == true || Etapa9 == true)) {
      digitalWrite(A1A, LOW);
      digitalWrite(A1B, LOW);
      delay(2000);
    }

    if (Etapa3 == true) {//if adicional donde el sensor 2 siempre este detectando el recipiente debajo de la bomba
      Etapa3 = false;
      Etapa4 = true;
      BombaA = true;
      Serial.println(" ");
      Serial.println("Bomba A dosificando... ");
    }

    if (BombaA == true && Etapa4 == true) {
      stepper1.setMaxSpeed(700);
      stepper1.setSpeed(550);
      stepper1.runSpeed();
    }

    if (Serial2.available() && (Etapa4 == true || Etapa6 == true || Etapa0 == false)) {  // se podria saca Et4 y Et6, y solo dejar Et0
      estado = Serial2.read();
    }

    if (Etapa4 == true && estado == 48) {//if adicional donde el sensor 2 siempre este detectando el recipiente debajo de la bomba
      Etapa4 = false;
      Etapa5 = true;
      BombaA = false;
      Serial.println("Bomba A Detenida... ");
    }

    if (BombaA == false && Etapa5 == true) {
      stepper1.stop();
      delay(2000);
      Etapa10 = false;
    }
    //-------------invierto el giro---------------------------------------------------------------------
    if (Etapa10 == false)
    {
      
      stepper1.move(-2000);
      
      while(stepper1.distanceToGo()!=0){
        stepper1.setSpeed(550);
        stepper1.runSpeedToPosition();
      }
      if (stepper1.distanceToGo()==0){
        Etapa11 = false;  
      }
      
    }
    //-------------------------------------------------------------------------------

    if (Etapa5 == true && Etapa11 == false) { //if adicional donde el sensor 2 siempre este detectando el recipiente debajo de la bomba
      Etapa5 = false;
      Etapa6 = true;
      BombaB = true;
      Etapa10 = true;
      Serial.println(" ");
      Serial.println("Bomba B dosificando... ");
    }

    if (BombaB == true && Etapa6 == true) {
      stepper2.setMaxSpeed(700);
      stepper2.setSpeed(550);
      stepper2.runSpeed();
    }

    if (Etapa6 == true && estado == 49) {//==49//if adicional donde el sensor 2 siempre este detectando el recipiente debajo de la bomba
      Etapa6 = false;
      Etapa7 = true;
      BombaB = false;
      Serial.println("Bomba B Detenida... ");
    }

    if (BombaB == false && Etapa7 == true) {
      stepper2.stop();
      delay(2000);
      Etapa12 = false;
    }

    //-------------invierto el giro---------------------------------------------------------------------
    if (Etapa12 == false)
    {
      
      stepper2.move(-2000);
      
      while(stepper2.distanceToGo()!=0){
        stepper2.setSpeed(550);
        stepper2.runSpeedToPosition();
      }
      if (stepper2.distanceToGo()==0){
        Etapa13 = false; 
        stepper2.stop();
      }
      
    }
    //-------------------------------------------------------------------------------

    if (Etapa7 == true && Etapa13 == false) {//if adicional donde el sensor 2 siempre este detectando el recipiente debajo de la bomba
      Plataforma = true;
      Serial.println(" ");
      Serial.println("Recipiente Dosificado: Saliendo... ");
      Etapa7 = false;
      Etapa8 = true;
      Etapa9 = true;
      Etapa12 = true;
      Serial.println(" ");
      Serial.println("Plataforma Encendida...");
    }

    if (Ir1 == 0 && Etapa9 == true && Etapa13 == false) {
      Plataforma = false;
      Serial.println(" ");
      Serial.println("Plataforma detenida... ");
      Etapa8 = false;
    }
  }

  if ((estado == 52 && Etapa0 == false && (Etapa3 == true || Etapa4 == true || Etapa5 == true || Etapa6 == true || Etapa7 == true)) || (Pulsador == LOW) && Puerta == true) {
    stepper1.stop();  //repetir para todos los motores que haya
    stepper2.stop();
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);

    if (Puerta_Abierta == true)
    {
      Serial.println("Puerta Abierta... Cierre la puerta por favor");
      Puerta_Abierta = false;
      delay (5000);
    }
  }
}
