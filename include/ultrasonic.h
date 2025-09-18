/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 ultrasonic Header File
*/

#ifndef ULTRASONIC_H_    //Include guard to prevent multiple inclusion of this header
#define ULTRASONIC_H_    //Define the header guard

#include <avr/io.h>       	//Allows access to AVR I/O port definitions

// Initializes the ultrasonic sensor hardware (pins, timer, interrupts)
void ultrasonicInit(void);

// Checks if Timer1 is set to capture on rising edge (return 1) or not (return 0)
int risingEdge();

// Measures and returns distance in centimeters using the ultrasonic sensor
int ultrasonicDistance();

// Randomly chooses a turn direction to avoid obstacles
void obstacleAvoid();

// Copy of the delay() in the millisMicrosDelay but for microseconds
void delayus(uint32_t requestedDelay);

#endif /* DRIVE_H_ */  // End of include guard