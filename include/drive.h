/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 Drive Header File
*/
#ifndef DRIVE_H_    //Include guard to prevent multiple inclusion of this header
#define DRIVE_H_    //Define the header guard

#include <avr/io.h>       	//Allows access to AVR I/O port definitions
//#include "usart.h"			//Allows use for usartSendString

// Initialize speed
void initSpeed(void);

// Setting to highest speed setting
void speedMax(void);

// Math Function to change speed
void variableSpeed(int percent);

// initialize PC pins 
void initDrive(void);

//Move motor forward subroutine
void forward(void);

//Move motor backward subroutine
void reverse(void);

//Take a right turn subroutine
void right(void);

//Take a left turn subroutine 
void left(void);

//Device stops  
void stop(void);

// Process movement commands based on character input
void movement(char ch);

// Process speed control commands based on character input
void speedlimit(char ch);

/*
// Processes a single received character, toggling an LED and calling movement/speed functions
void coreFunction();
*/


#endif /* DRIVE_H_ */  // End of include guard
