# Controlador de la intensidad y el color del LED RGB con la técnica de PWM

## Materia
- Circuitos Digitales y Microcontroladores de la carrera Ingeniería en Computación de la Universidad Nacional de La Plata

## Grupo
- G21 

## Integrantes
- Ivan Sandoval 
- Juan Manuel Rodriguez 

## Descripción del Proyecto
En el siguiente proyecto se trata de resolver un sistema, en el cuál se permita poder seleccionar y modificar la intensidad de los colores de un LED RGB, también el sistema permitirá modificar el brillo del LED requerido mediante el uso de un Potenciómetro.

## Las tecnologías utilizados fueron 
- placa Arduino uno
- atmega382p
- lenguaje de programación C
- Proteus
- Potenciometro
- LED RGB

## Instalación 
1. Instalar el Microchip Studio
2. Instalar Proteus
3. Clonar el repositorio 
4. Abrir el archivo del proyecto denominado CDyM-2024-TP4-G21 ubicado en la carpeta de directorios CDyM-2024-TP4-G21\Microchip\CDyM-2024-TP4-G21
5. Realizar la compilación del proyecto 
6. Abrir el archivo de la simulación en Proteus denominado CDyM-2024-TP4-G21 que se ubica en la carpeta de directorios CDyM-2024-TP4-G21\Proteus
7. Ejecutar el la simulación en Proteus

## Requerimientos a verificar en el proyecto
- Generar tres señales PWM de frecuencia mayor o igual a 50Hz y con una resolución de 8 bits cada una, en los terminales PB1,PB2 y PB5 del atmega328p.
- Permitir seleccionar la proporción de color del LED RGB para cada LED (de 0 a 255) para obtener un color resultante.
- Permitir seleccionar mediante un comando en la interfaz serie UART0 del atmega328p, cual proporción de color desea modificar. Enviar ´R´ para modificar el rojo, ´G´ para el verde y ´B´ para el azul.
- Permitir poder utilizar el potenciómetro (resistencia variable) conectado al terminal ADC3 del atmega328p para poder modificar el brillo del color seleccionado.

