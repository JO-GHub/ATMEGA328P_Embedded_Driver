/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
Autonomous navigation robot with remote temperature sensing
*/

#define F_CPU 16000000UL  //Defines the CPU frequency as 16MHz
#include <avr/io.h>
#include <stdint.h>  //for uint_ variables
#include <stdio.h>   //for sprintf function

#include "usart.h"
#include "temp.h"
#include "ultrasonic.h"
#include "millisMicrosDelay.h"
#include "drive.h"

void initTempReading();
void initADC();
uint16_t analogRead();
int conversionComplete();

int main(void)
{    
    usartInit();
    initTempReading();
    initADC();
    initSpeed();
    initDrive();
    millisMicrosDelayInit();
    ultrasonicInit();
    variableSpeed(8);
    
    char temp_reading[20];
    char voltage_reading[20];
    
    while (1)
    { 
        // Check for temperature reading request
        char ch;
        ch = usartReadChar();
        if (ch == 't')
        {
                float adc_value = 0;
                float voltage = 0;
                float temperature = 0;
                
                // Get ADC reading
                adc_value = analogRead();
                
                // 5V ref divided by 10bit ADC
                voltage = (adc_value / 1024.0) * 5.0;
                temperature = voltage * 100.0;

                // Format voltage string using sprintf
                sprintf(voltage_reading, "%.4fV\r\n\n", voltage);
                
                // Format temperature string using sprintf
                sprintf(temp_reading, "%.2fC\r\n\n", temperature);
                
                // Send formatted strings to USART
                usartSendString(voltage_reading);
                usartSendString(temp_reading);
            }
        }
        
        // Movement and obstacle avoidance
        forward();

        while (ultrasonicDistance() < 50)
        {
            obstacleAvoid();
        }
    }
    
    return 0;
}
