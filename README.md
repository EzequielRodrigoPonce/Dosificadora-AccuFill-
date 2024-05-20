<p align="center" width="100%">
    <img width="15%" src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Readme.md/321138189_722314939154857_3310166726490044259_n.jpg" align="left">
    <img width="15%" src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Readme.md/378230559_797453282383428_4968693939392363229_n.jpg" align="right">
</p>
<br><br><br>


                
<h1 align="center">Dosificadora Peristáltica</h1>
<br>
<br>
<h2 align="center">Integrantes:</h2>
<h3 align="center">Ponce, Rodrigo Ezequiel</h3>
<h3 align="center">Obermann, Cristian</h3>


<br><br><br>

Este proyecto se propone brindar una alternativa más barata, personalizable e intuitiva a la dosificación de líquidos para la industria alimenticia. En el mercado, este tipo de máquinas se pueden obtener una gran variedad de precios, caudales y precisión, pero su valor es muy alto en contraste con los componentes que forman el equipo, que pueden ser adquiridos por un precio relativamente bajo. Este proyecto además tiene como objetivo facilitar el uso mediante una interfaz de usuario amigable que se controle desde un Smartphone o una computadora, generalmente las dosificadoras con este tipo de funciones son de las más costosas de su tipo.

## Descripción:

El proyecto consiste en desarrollar una solución económica y funcional para la dosificación de dos fluidos denominados componente “A” y componente “B” para obtener una preparación o distintas formulaciones que la industria alimenticia considere necesarias a partir de dos componentes.
Se construirá un cubículo donde se concentran todos los componentes electrónicos y el espacio de dosificación que funcionará con un motor eléctrico y diversos sensores que harán al automatismo y control del proceso. Asimismo, se construirán dos bombas peristálticas encargadas de la dosificación.
Se tendrá un espacio donde colocar un recipiente para ser leído por un sensor que permite que se aplique la cantidad programada de un determinado fluido “A” Y “B”, luego se tendrá la formulación deseada. 
Este prototipo está destinado a ser construido como modelo de prueba para la industria alimenticia, con un nivel de precisión y tolerancia acorde a dicha industria y etapa del proyecto.

## Especificación de Requerimientos de la Dosificadora

El usuario podrá especificar la cantidad de líquido y las proporciones del líquido A y B que se dosificarán mediante un servidor web, través de un Smartphone o computadora, siguiendo una dirección de internet ó escaneando un código QR, se podrá controlar con una interfaz intuitiva.

Una vez especificadas las proporciones a dosificador, se deberá transportar un recipiente vacío sobre una plataforma que se encuentra dentro del equipo, en el punto donde se deposita el recipiente está tendrá un sensor óptico capaz de detectar su presencia, esto hará que la plataforma traslade el recipiente y se detenga debajo de la manguera a la salida de la bomba peristáltica.
Los dos recipientes que contienen los líquidos A y B estarán encima de balanzas de precisión. Estas ayudaran a mejorar la precisión con la que se distribuyen los líquidos.
Primero se dosifica la cantidad de líquido A según lo especificado por el usuario y luego el sistema, mediante la balanza, calcula la cantidad de líquido A que se distribuyó y con esos valores determina la cantidad de líquido B que se proporcionará a continuación.  
Las bombas peristálticas serán capaces de distribuir líquido dentro de un rango de caudal de 100 a 1500 mL/min.    

## Proceso de Peristálsis:
Las bombas peristálticas funcionan cuando los rodillos comprimen la manguera al girar, creando un vacío que succiona fluido a través de esta. En este tipo de bomba, solo la manguera de elastómero flexible entra en contacto con el fluido, eliminando el riesgo de que la bomba contamine el fluido o a la inversa.
En la Imagen se puede observar el fluido entrando en la manguera de la bomba, atrapado por el rodillo del cabezal de bombeo, y expulsado cuando el próximo rodillo pasa sobre la manguera. Al girar los rodillos, se forma un vacío en la manguera, succionando más fluido, para el próximo paso del rodillo.
El cierre total de la manguera al ser comprimida entre el rodillo y la pista (oclusión) proporciona a la bomba una acción de desplazamiento positivo, evitando el reflujo y eliminando la necesidad de válvulas reguladoras cuando la bomba no está en funcionamiento.


<p align="center" width="100%">
    <img width="33%" src="https://i.makeagif.com/media/1-27-2016/YvQtiC.gif">
</p>

<br>
<br>
<br>
<p align="center" width="100%">
    <img width="93%" src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Readme.md/GIF%20Parte%201.gif">
</p>
<br>
<br>
<br>

<p align="center" width="100%">
    <img width="93%" src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Readme.md/GIF%20Parte%202.gif">
</p>

<br>
<br>
<br>
<p align="center" width="100%">
    <img width="93%" src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Readme.md/GIF%20Parte%203_1.gif">
</p>
<br>
<br>
<br>


<table align="center" style="margin-left: auto; margin-right: auto;">
<tr>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Ensamblando%20bomba.jpg" width="300"> <br>Ensamblaje de Bomba </td>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Probando%20bomba%20con%20el%20primer%20motor%20CC.jpg" width="300"> <br>Testeo </td>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Revisi%C3%B3n%20de%20pines.jpg" width="300"> <br>Cableado de Circuito </td>
</tr>
<tr>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Imagen%20de%20WhatsApp%202023-12-01%20a%20las%2023.33.35_a418374a.jpg" width="300"> <br>Calibración </td>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Preparativos%20para%20la%20estructura.jpg" width="300"> <br>Lijado de Dosificadora </td>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Pintando%20la%20estructura%20del%20prototipo.jpg" width="300"> <br>Pintado de Dosificadora </td>
</tr>
<tr>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/distribuci%C3%B3n%20y%20montaje%20de%20cables%20en%20la%20base.jpg" width="300"> <br>Armado Final </td>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/colocaci%C3%B3n%20de%20luces%20en%20cabina%20de%20dosificaci%C3%B3n%20y%20bombas.jpg" width="300"> <br>Vista Frontal  </td>
<td><img src="https://raw.githubusercontent.com/EzequielRodrigoPonce/Dosificadora-AccuFill-FI-UNLZ/main/Imagenes/Probando%20comunicaci%C3%B3n%20serial%20entre%20pagina%20y%20motores.jpg" width="300"> <br>¡Dosificadora Completada! </td>
</tr>
</table>
<br>
<br>
<br>

[![Dosificadora Multi Canal](http://i3.ytimg.com/vi/ZArngSEx4A0/hqdefault.jpg)](https://www.youtube.com/watch?v=ZArngSEx4A0 "Dosificadora Multi Canal")
