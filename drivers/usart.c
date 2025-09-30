/* 
Name: Joseph Oddi Obong
Student ID: B00165928
Email: B00165928@mytudublin.ie

Programme: TU807
Module: Microcontroller Applications

Purpose:
CA02 USART Implementation File
*/
#include <avr/io.h> //Allows access to AVR I/O port definitions
#include "usart.h"  //Include the header file

/*****************************************************
 * This function sets up the USART for 9600 8N1
 ****************************************************/
void usartInit(void)
{
    //Enables transmitter and receiver
    UCSR0B |= ((1<<TXEN0) | (1<<RXEN0)); 

    // Set UART Mode (asynchronous UART)
    UCSR0C &= ~(1<<UMSEL01); 
    UCSR0C &= ~(1<<UMSEL00); 

    //Set Parity Mode to none
    UCSR0C &= ~((1<<UPM01) | (1<<UPM00));

    //Set Stop bits to 1
    UCSR0C &= ~(1<<USBS0); 

    //Set Data size to 8 bits
    UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));
    UCSR0B &= ~(1<<UCSZ02);

    //Set Baud rate to 9600
    UCSR0A &= ~(1<<U2X0); //Don't double UBRR
    UBRR0 = 103; //Baud rate to 9600 as per table

    DDRB |= (1<<5); //Set PB5 as output (used for LED indicator)
}

/*****************************************************
 * This function should return a 1 if a char has been
 * received and a 0 if not. 
 ****************************************************/
//Checks the USART Receive Complete flag (RXC0) in UCSR0A register
//Returns 1 if data is available in the receive buffer, returns 0 otherwise
uint8_t usartCharReceived(void)
{
    if (UCSR0A & 1<<RXC0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************
 * This function should simply return the received 
 * char by copying it from the UDR register.
 *
 * N.B. Thus function should only be called after 
 * a call to usartCharReceived() returns a 1.
 ****************************************************/
//Reads the UDR0 register and returns the received character
//Reading UDR0 automatically clears the receive buffer
char usartReadChar(void)
{
    return UDR0;
}

/*****************************************************
 * This function should send a single char and wait
 * until the transmission is complete.
 ****************************************************/
void usartSendChar(char c)
{
	//Wait for empty buffer
	while(!(UCSR0A & (1<<UDRE0)));

	//Send character to buffer
	UDR0 = c;
}

/*****************************************************
 * This function should send a string of chars and 
 * wait until the transmission is complete.
 ****************************************************/
void usartSendString(char str[])
{
	int i = 0;

	while (str[i] != '\0')
	{
		usartSendChar(str[i]);
		i++;
	}
}
