/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 BOT Temp Implementation File
*/

#include <avr/io.h>
#include <stdint.h>  //for uint_ variables
#include "temp.h" //include temp header

void initTempReading()
{
    DDRC &= ~(1<<5); // Set PC5 as input
}

void initADC()
{
    // Reset registers for clean initialization
    ADMUX = 0;
    ADCSRA = 0;
    
    // AVcc with external capacitor at AREF pin
    ADMUX |= (1<<REFS0);

    // Prescale to 128 as ADC prefers between 50kHz - 200kHz
    ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));
    
    // ADC Enable pin
    ADCSRA |= (1<<ADEN);
}

uint16_t analogRead()
{
    // Clear MUX bits
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0)); 
    // Set to A5 (PC5)
    ADMUX |= ((1<<MUX2) | (1<<MUX0));

    // Start conversion
    ADCSRA |= (1<<ADSC);

    // Wait while conversion is in progress
    while (conversionComplete() == 1);

    return ADC;
}

int conversionComplete()
{
    // Check if conversion is complete
    if (ADCSRA & (1 << ADSC))
    {
        return 1; // If ADSC is HIGH return 1 (conversion in progress)
    }
    else
    {
        return 0; // If ADSC is LOW return 0 (conversion complete)
    }
}