# USB-ISS_minimu9_and_buttons

## Descripción general
Tutorial de conexión y utilización en Ubuntu del módulo USB-ISS conectado al Pololu MinIMU-9 v2 (Acelerómetro, Magnetómetro y Giroscopio) y 2 push buttons en código C con el propósito de la utilizar los datos de salida en programas más avanzados.

## Pre-requisitos
Se deberá de contar con los siguientes elementos:
* Pololu MinIMU-9 v2 o versiones más actualizadas, por ejemplo: [MinIMU-9 v5](https://www.pololu.com/product/2738) (Al ser una versión diferente a la utilizada, se requiere leer el apartado de [Compatibilidades](#compatibilidades))
* Módulo de comunicación USB-ISS (Puede ser comprado de [México](https://store.robodacta.mx/interfaces-y-programadores/interfaces/interfaz-usb-iss/) o [Estados Unidos](https://www.robotshop.com/en/devantect-usb-to-i2c-spi-serial-interface.html))
* Cable [USB A macho a B macho](https://www.trossenrobotics.com/store/p/6611-USB-A-Male-to-B-Male-6ft-Cable.aspx)
* Dos [Push-buttons](https://www.sparkfun.com/products/8605)
* Dos [resistencias de 1K Ohms](https://www.sparkfun.com/products/14492)

## Componentes
<p align="center">
  <img width="260" length="100" src="https://www.robot-electronics.co.uk/images/usb-iss-300.png">
</p>

El módulo de comunicación USB-ISS es un dispositivo que provee de una completa interfaz entre la PC e I2C, SPI, Puerto Serial o una Entrada Analógica o Digital de propósito general, con el fin de hacer más fácil la transmisión o recepción de datos. Es necesario conocer el proceso de comunicación, en este caso para el protocolo I2C por lo que se necesita leer su documentación a detalle [1]

<p align="center">
  <img width="260" length="100" src="https://a.pololu-files.com/picture/0J4037.600x480.jpg?db7cf96bdb8f6b5fa41ccef67ecbf90b">
</p>

El Pololu MinIMU-9 es un dispositivo que contiene tres sensores sensores (Giroscopio, Magnetómetro y Acelerómetro) en una interfaz I2C que accede a nueve mediciones independientes de rotación, magnéticas y aceleración, mediante sus diferentes direcciones, las cuales se encuentran en las siguientes referencias [2-3].

## Diagrama de conexión

<p align="center">
  <img width="650" length="250" src="https://github.com/JuanCarlos-MA/USB-ISS_minimu9_and_buttons/blob/master/connection_diag.png">
</p>

Con este diagrama se permite establecer un ejemplo de conexión con los entre el USB-ISS, MinIMU-9 y los dos Push-button para poder realizar programas o funciones más avanzadas en róbotica o en [IoT](https://www.wired.co.uk/article/internet-of-things-what-is-explained-iot) (Internet de las Cosas; IoT por sus siglas en inglés).

## Compatibilidades
Debido a que el MinIMU-9 v2 es un dispositivo que ha sido descontinuado por versiones más actualizadas tal y cómo el MinIMU-9 v5 contiene diferentes tipos de sensores, es necesario revisar a detalle las direcciones para accesar al dispositivo y para poder leer los datos de las 9 mediciones [4-5].

## Proceso de utilización

Al conectar el USB a la computadora con Ubuntu, es necesario verificar que el dispositivo aparece como algún puerto ACM, p. ej. `/dev/ttyACM0`, así como es de suma importancia habilitar los permisos de lectura de dicho dispositivo para ello se necesita escribir en una linea de comandos:
```
sudo chmod a+rw /dev/ttyACM0 
```
Para utilizar el proyecto, se puede descargar o clonar y posteriormente utilizando el compilador **gcc** se podrá correr el programa con las siguientes instrucciones en una Terminal: 

```
cd ~
git clone https://github.com/JuanCarlos-MA/USB-ISS_minimu9_and_buttons.git
cd ~/USB-ISS_minimu9_and_buttons-master/USB-ISS_MinIMU-9_buttons/
gcc -o minimu minimu9.c
./minimu
```
Finalmente, al correr el programa ejecutable `./minimu` se deberá mostrar una salida similar a la siguiente:
```
USB-ISS Module ID: 7 
USB-ISS Software v: 6 

 
 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   DATOS DE LOS SENSORES   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 

    Acelerómetro			    Magnetómetro		              Giroscopio		  Botones 

  X        Y        Z			 X        Y        Z			 X        Y        Z		  B1   B2 
-0.016  -0.031  -1.094 			209	-1121 	-864			157	-70       41		 OFF   OFF
 
0.000  -0.016  -1.078 			209	-1121 	-865			151	-80       80		 OFF   OFF
 
0.000  -0.031  -1.078 			210	-1121 	-863			147	-92       51		 OFF   OFF
 
-0.016  -0.016  -1.094 			209	-1121 	-865			126	-86       58		 ON   ON
 
-0.016  -0.016  -1.078 			210	-1121 	-864			143	-111       82		 OFF   ON
```
Esto demuestra que funciona correctamente, para observar una salida del programa más completo, se adjuntó un archivo .txt, llamado [ejemplo-salida.txt](USB-ISS_MinIMU-9_buttons/ejemplo-salida.txt).

## Autor

**Juan Carlos Martínez Aguilar** *Estancia de Investigación en Robots Humanoides*

## Referencias
1. Anónimo, "Robot Electronics," [Online]. Available: https://www.robot-electronics.co.uk/htm/usb_iss_tech.htm.
2. STMicroelectronics, "LSM303DLHC Ultra compact high performance e-compass 3D accelerometer and 3D magnetometer module," April 2011. [Online]. Available: https://www.pololu.com/file/0J564/LSM303DLHC.pdf. [Accessed 10 January 2020].
3. STMicroelectronics, "L3GD20 MEMS motion sensor: three-axis digital output gyroscope," February 2013. [Online]. Available: https://www.pololu.com/file/0J563/L3GD20.pdf. [Accessed 08 January 2020].
4. STMicroelectronics, "LSM6DS33 iNEMO inertial module: always-on 3D accelerometer and 3D gyroscope," October 2015. [Online]. Available: https://www.pololu.com/file/0J1087/LSM6DS33.pdf. [Accessed 31 January 2020]. 
5. STMicroelectronics, "LIS3MDL Digital output magnetic sensor: ultra-low-power, high-performance 3-axis magnetometer," May 2015. [Online]. Available: https://www.pololu.com/file/0J1089/LIS3MDL.pdf. [Accessed 31 January 2020].
