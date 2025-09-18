/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 ultrasonic Implementation File
*/

#include "ultrasonic.h"    // Include the header file for ultrasonic functions
#include <avr/io.h>        // Allows access to I/O definitions
#include <avr/interrupt.h> // For ISR and interrupt handling functions
#include <stdio.h>         // For sprintf() used to format output strings
#include <stdlib.h>        // For rand() used in obstacleAvoid()
//#include "usart.h"         // For USART functions to transmit the distance data
#include "millisMicrosDelay.h" // For delay() and other timing functions
#include "drive.h"         // For drive functions used in obstacleAvoid()

// Global variables for distance measurement
uint8_t DistanceCapture = 0;   // Flag to indicate if a complete echo pulse was captured (0 = not captured, 1 = captured)
// Timer values at the start and end of the echo pulse
uint16_t startCount = 0;
uint16_t stopCount = 0; 


void ultrasonicInit(void)
{
    // Pin configuration
    DDRB &= ~(1 << 0);       // Set PB0 as input (Echo pin from ultrasonic sensor)
    DDRD |= (1 << 7);        // Set PD7 as output (Trigger pin to ultrasonic sensor)

    // Timer1 configuration for input capture
    TCCR1B |= (1 << CS11);   // Set Timer1 prescaler to 8 (2MHz timer frequency - each tick is 0.5μs)
    TCCR1B |= (1 << ICES1);  // Set to capture on rising edge initially
    TIMSK1 |= (1 << ICIE1);  // Enable input capture interrupt

    sei();                   // Enable global interrupts
}

int risingEdge()
{
    // Check if Input Capture is set to detect rising edge (ICES1 bit)
	if (TCCR1B & (1 << ICES1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


ISR(TIMER1_CAPT_vect)
{
    if(risingEdge() == 1) // Check if pin is at the rising edge
    {
        startCount = ICR1;    // Store the timer value at the rising edge (start of echo pulse)
        // Configure for falling edge detection next
        TCCR1B &= ~(1 << ICES1);  // Clear ICES1 bit to detect falling edge next
    }
    else
    {
        stopCount = ICR1;     // Store the timer value at the falling edge (end of echo pulse)
        // Configure for rising edge detection next
        TCCR1B |= (1 << ICES1);   // Set ICES1 bit to detect rising edge next
        DistanceCapture = 1;  // Set flag to indicate a complete pulse has been measured
    }   
}

int ultrasonicDistance()
{
	// Variables for distance calculation
   	uint16_t pulseTime=0;
    uint8_t distance = 0;
    char str[10];  // Buffer to store the distance as a string for transmission

   
   	// Generate trigger pulse for the ultrasonic sensor
    PORTD |= (1 << 7);    // Set trigger pin high
    delayus(10);        // Keep trigger high for 10 microseconds (fixed from ms to us)
    PORTD &= ~(1 << 7);   // Set trigger pin low
    
    delay(60);        // Wait for the measurement to complete 
    
    if(DistanceCapture == 1)  // Check if a complete echo pulse was captured
    {
        DistanceCapture = 0;  // Reset the capture flag for the next measurement
        
        // Calculate distance
        pulseTime = (stopCount - startCount) / 2;  // Calculate pulse duration in microseconds (divide by 2 due to Timer1 running at 0.5μs per tick)
        distance = pulseTime / 58;                 // Convert time to distance in cm (Sound travels at ~343m/s, so round-trip time for 1cm is ~58μs)
        
        /*
        // Send the distance via USART
        sprintf(str, "%d\n", distance);  // Convert distance to string with newline
        usartSendString(str);            // Transmit the distance string via USART
        */
    }
       
    delay(200);       // Delay between measurements (reduced from 1000ms to increase sampling rate)
   
   	return distance;  // Return calculated distance	
}

void obstacleAvoid()
{
    // Randomly choose direction to turn when obstacle detected
    int escape = (rand() % 2);
    if (escape == 0)
    {
        stop();
        delay(100);
        right();
        delay(1000);
        stop();
        delay(100);
    }
    else
    {
        stop();
        delay(100);
        left();
        delay(1000);
        stop();
        delay(100);
    }
}

void delayus(uint32_t requestedDelay)
{
    uint32_t start = micros();
    while ((micros() - start) < requestedDelay)
    { 
		// Do nothing. Delayed until micros() reaches requested delay
    }
}



