/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 millisMicrosDelay Implementation File
*/

#include "millisMicrosDelay.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define microsTick 4UL  // Microseconds per timer tick, using integer math to avoid floats

uint32_t millisTime = 0;  // Tracks elapsed milliseconds
uint32_t microsTime = 0;	//Tracks elapsed microseconds
uint8_t currentCount = 0;	// For TIMER current count variable


// Compare Match interrupt service routine for Timer2
ISR(TIMER2_COMPA_vect)
{
    // Increment millisecond counter each time OCR2A is reached
    millisTime++;
}


void millisMicrosDelayInit(void)
{
	// Turn off interrupts
	cli();

    // Enable CTC mode
    TCCR2A &= ~((1 << WGM22) | (1 << WGM20)); 
    TCCR2A |=  (1 << WGM21);  
    
    
    // Prescaler = 64 ; CS = 100
    // Use prescaler 64 to achieve a 4 µs timer tick (16 MHz / 64)
    TCCR2B &= ~((1 << CS21) | (1 << CS20));
    TCCR2B |=  (1 << CS22);
    
    
    // Enable Compare Match A interrupt 
    // 250 ticks x  4µs = 1ms
    TIMSK2 |= (1 << OCIE2A);
    OCR2A = 249;

    // Turn on interrupts
    sei();
}


uint32_t millis(void)
{
	cli(); 

	// Read millis elapsed
    uint32_t current;               
    current = millisTime;

    sei();
     
    return current;
}

uint32_t micros(void)
{
	
	currentCount = TCNT2;
	microsTime = (millisTime * 1000) + (currentCount * microsTick);
	
	return microsTime;	
}


void delay(uint32_t requestedDelay)
{
    uint32_t start = millis();
    while ((millis() - start) < requestedDelay)
    { 
		// Do nothing. Delayed until millis() reaches requested delay
    }
}
