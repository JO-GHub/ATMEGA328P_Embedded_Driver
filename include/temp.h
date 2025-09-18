/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 BOT Temp Header File
*/

#ifndef TEMP_H_
#define TEMP_H_

#include <stdint.h>  //for uint_ variables

void initTempReading();

void initADC();

uint16_t analogRead();

int conversionComplete();

#endif //TEMP_H_
