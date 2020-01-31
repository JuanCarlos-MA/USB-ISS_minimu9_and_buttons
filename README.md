# USB-ISS_minimu9_and_buttons

## Descripción general
Tutorial de utilización del módulo USB-ISS conectado al Pololu MinIMU-9 v2 (Acelerómetro, Magnetómetro y Giroscopio) y 2 push buttons en código C con el propósito de la utilizar los datos de salida en programas más avanzados.

## Pre-requisitos
Se deberá de contar con los siguientes elementos:
* Pololu MinIMU-9 v2 o versiones más actualizadas, por ejemplo: [MinIMU-9 v5](https://www.pololu.com/product/2738) (Al ser una versión diferente a la utilizada, se requiere leer el apartado de [Compatibilidades](#compatibilidades))
* Módulo de comunicación [USB-ISS](https://www.robot-electronics.co.uk/usb-iss-enhanced-usb-i2c-module.html)
* Cable [USB A macho a B macho](https://www.trossenrobotics.com/store/p/6611-USB-A-Male-to-B-Male-6ft-Cable.aspx)
* Dos [Push-buttons](https://www.sparkfun.com/products/8605)
* Dos [resistencias de 1K Ohms](https://www.sparkfun.com/products/14492)

## Componentes
<p align="center">
  <img width="260" length="100" src="https://www.robot-electronics.co.uk/images/usb-iss-300.png">
</p>

El módulo de comunicación USB-ISS es un dispositivo que provee de una completa interfaz entre la PC e I2C, SPI, Puerto Serial o una Entrada Analógica o Digital de propósito general, con el fin de hacer más fácil la transmisión o recepción de datos.

<p align="center">
  <img width="260" length="100" src="https://a.pololu-files.com/picture/0J4037.600x480.jpg?db7cf96bdb8f6b5fa41ccef67ecbf90b">
</p>


## Diagrama de conexión

<p align="center">
  <img width="650" length="250" src="https://github.com/JuanCarlos-MA/USB-ISS_minimu9_and_buttons/blob/master/connection_diag.png">
</p>

El módulo USB-ISS mediante el protócolo I2C el cuál es el utilizado para el MinIMU-9,
## Compatibilidades

## Autor

**Juan Carlos Martínez Aguilar** *Estancia de Investigación (Invierno 2020)*

## Referencias
1. Anónimo, "Robot Electronics," [Online]. Available: https://www.robot-electronics.co.uk/htm/usb_iss_tech.htm.
2. STMicroelectronics, "LSM303DLHC Ultra compact high performance e-compass 3D accelerometer and 3D magnetometer module," April 2011. [Online]. Available: https://www.pololu.com/file/0J564/LSM303DLHC.pdf. [Accessed 10 January 2020].
3. STMicroelectronics, "L3GD20 MEMS motion sensor: three-axis digital output gyroscope," February 2013. [Online]. Available: https://www.pololu.com/file/0J563/L3GD20.pdf. [Accessed 08 January 2020].

