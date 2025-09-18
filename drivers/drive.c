/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA03 Drive Implementation File
*/

#include "drive.h"         // Include the header file
#include <avr/io.h>        // Allows access to AVR I/O port definitions
//#include "usart.h"         // Allows use of usartSendString (and other USART functions)
#include "millisMicrosDelay.h" // For precise timing functions, e.g. delay()

//Motor control pin mapping based on physical bot wiring
#define rightforward    PC1
#define rightbackward   PC0
#define leftforward     PC2
#define leftbackward    PC3
#define maxrightmotor   200
#define maxleftmotor    255


void initSpeed(void)
{
    // Set OC0A and OC0B as outputs
    DDRD |= (1 << PD6) | (1 << PD5); 

    //Set to Fast PWM BOTTOM to MAX
    TCCR0A |= ((1<<WGM00) | (1<<WGM01)); 
    TCCR0B &= ~(1<<WGM02);

    //No prescaling
    TCCR0B |= (1<<CS00);
    TCCR0B &= ~((1<<CS01) | (1<<CS02));

    //Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode).
    TCCR0A |= (1<<COM0A1);
    TCCR0A &= ~(1<<COM0A0); 

    //Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode).
    TCCR0A |= (1<<COM0B1);
    TCCR0A &= ~(1<<COM0B0); 
}

void speedMax(void)
{
    // Set both motors to their maximum speed values
    OCR0A = maxrightmotor;//right motor
    OCR0B = maxleftmotor;//left motor
}

void variableSpeed(int percent)
{
    // Calculate and set speeds based on input percentage (0-9)
    OCR0A = (maxrightmotor/100) * (percent*10);//right motor
    OCR0B = (maxleftmotor/100) * (percent*10);//left motor
}

void initDrive(void)
{
    //DDRC reg pins 0 to 3 are set to make PortC 0 to 3 as outputs 
    DDRC = 0x0F; // Sets PC0, PC1, PC2, PC3 to output

    // Configure LED pin (PB5) as output
    DDRB |= (1 << 5);
}

void stop(void)
{
    //Clear all motor pins to create a stop
    PORTC &= ~((1 << rightforward) | (1 << rightbackward) | (1 << leftforward) | (1 << leftbackward));
}

void forward(void)
{
    stop();
    
    //Set forward motor pins (PC1, PC2) high by OR'ing their bit masks with PORTC
    PORTC |= (1 << rightforward) | (1 << leftforward);
    //Equals = 0000 0110
}

void reverse(void)
{
    stop();
    
    //Set reverse motor pins (PC0, PC3) high by OR'ing their bit masks with PORTC
    PORTC |= (1 << rightbackward) | (1 << leftbackward);
    //Equals = 0000 1001
}

void right(void)
{
    stop();
    
    //Set right turn motor pins (PC0, PC2) high by OR'ing their bit masks with PORTC
    PORTC |= (1 << rightbackward) | (1 << leftforward);
    //Equals = 0000 0101
}

void left(void)
{
    stop();
    
    //Set left turn motor pins (PC1, PC3) high by OR'ing their bit masks with PORTC
    PORTC |= (1 << rightforward) | (1 << leftbackward);
    //Equals = 0000 1010
}

/*
void coreFunction()
{
    //Turn LED on when character received
    PORTB |= (1 << 5);

    // Get a character from USART
    char ch;
    ch = usartReadChar();

    // Check input character and call appropriate movement function
    if (ch == 'F')
    {
        forward();
    }
    if (ch == 'L')
    {
        left();
    }
    if (ch == 'R')
    {
        right();
    }
    if (ch == 'B')
    {
        reverse();
    }
    if (ch == 'S')
    {
        stop();
    }
    // If input is a digit between 1-9, set speed as percentage
    if (ch >= '1' && ch <= '9')
    {
        int percent = ch - '0'; // Convert ASCII character to integer value
        variableSpeed(percent);
    }

    // If input is 'q', set motors to maximum speed
    if (ch == 'q')
    {
        speedMax();
    }   

    //Short delay to make LED blink visible
    delay(100);
    
    //Turn LED off
    PORTB &= ~(1 << 5);
} 
*/