# Temparature-Module
![PCB-Front](https://github.com/alcruzr/Temparature-Module/assets/87552616/6c34e60f-f3cb-4130-8d9b-7562a5bdf470)  ![PCB-Back](https://github.com/alcruzr/Temparature-Module/assets/87552616/20d685b5-eb02-4ad3-b97e-49fca263c95e)


This is a temperature sensor module that implements the LM35 temp. sensor and displays the temperature on an OLED screen that is controlled by an Arduino Nano. The module is powered by a 9V battery that is stepped down to 6V, via a linear regulator, to power all components. The temperature from the LM35 is given in C, which is then converted to F by a series of opamp circuits. 

The overall circuit can be seen below.
![Temp Sensor Circuit](https://github.com/alcruzr/Temparature-Module/assets/87552616/f2c656c4-d4c5-4485-8ac4-7615ec7dacb4)


The equation to convert from Celsius to Fahrenheit is: F=(C x 9/5) + 32

The first OPAMP will be configured as a non-inverting amplifier and have the gain set to 9/5 perform the multiplication and the second OPAMP will be configured as a non-inverting summer circuit which will add the value of 32.

The red, green, and blue leds are used for visual indication of different temperature ranges. red: temp > 80F, green: 60F < temp < 70F, blue: temp < 60F

PCB gerber zip file and BOM for all parts are also included. 
