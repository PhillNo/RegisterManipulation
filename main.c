/*
 * BlinkInterrupt.cpp
 *
 * Created: 13-Jan-20 2:06:25 PM
 * Author : PhillNo
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
	SREG &= ~(1 << 7);		//disable global interrupts (Status Register section 11.3 of data sheet)
	
	PRR = ~(1 << 3);		//stop clocking unused peripherals to save power (1 means disabled). (Power Reduction Register section 14.10 and 14.12.3)
	
	DDRB |= (1 << 5);		//enable output mode for bit 5 of port B (I/O ports section 18. Built-in LED on Arduino Uno)
	
	GTCCR = 0B10000011;		//halt all timers (not necessary for this example). (General Timer/Counter Control Register section 19.9.4)
	
	TCCR1A = 0;				//Timer1 is controlled by 2 registers (TC1 Control Register A: 20.14.1.  TC1 Control Register B: 20.14.2.)
	TCCR1B = 0;				//reset both registers
	
	TCCR1A = 0;				//configure both registers of Timer1
	TCCR1B = 0B0000011;		//use 64 as prescaler on CPU clock as clock source
							//Note: time is not being converted to base 10, a useful approximation for 0.5 seconds is used instead
	
	TIMSK1 = 1;				//enable timer over flow interrupt (Timer/Counter 1 Interrupt Mask Register: 20.14.12)
							//TIFR1 flag bit will automatically clear when ISR runs (TC1 Interrupt Flag Register: 20.14.13)
	
	SREG |= (1 << 7);		//enable global interrupts
	
	GTCCR &= 0B01111111;	//start timers
	
	
    while (1)
    {
    }
}

ISR(TIMER1_OVF_vect){		//define the interrupt for a timer overflow event
	PORTB ^= (1 << 5);		//use XOR operation to toggle the 5th bit.
}
