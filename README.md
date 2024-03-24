# Reverse Car Parking Assistance System
This project implements a reverse car parking assistance system using LPC2129 microcontroller and CAN protocol. The system helps drivers park their vehicles safely by providing assistance in detecting obstacles behind the vehicle. There are two parts of this system: the front side of the car or the dashboard and the rear side of the car. Both the CAN nodes are connected to the CAN Bus.
## Front Side
 The front side has the following components:
 * CAN controller
 * LED
 * Switch
 * Alphanumeric LCD
 * Buzzer

The parking assistance system is turned on and off using the switch. The LED is on when the system is on and off when the system is off.
## Rear Side
The rear side has the following components: 
 * CAN controller
 * Potentiometer

Here, the potentiometer acts as an ultrasonic sensor which sends distance between the car and the object to the microcontroller via ADC.
## Working
1. When the switch is pressed for the first time, the system is activated.
2. The front side sends a remote frame to the rear side to request the data frames.
3. The rear side takes reading from potentiometer and send the data frame to the front side every 100 ms.
4. The front side receives the data frame and displays the distance between the car and the object on the LCD.
5. If the distance is within 400 cm, the buzzer starts beeping:
 * 300-400 cm: 1.5 sec beep interval
 * 200-300 cm: 1 sec beep interval
 * 100-200 cm: 500 ms beep interval
 * 50-100 cm: 100 ms beep interval
 * < 50 cm: Continuous beeping
6. If the switch is pressed the second time front side send a data frame to the rear side to stop the transmission and the LED is turned off. The reverse parking system is also turned off.
