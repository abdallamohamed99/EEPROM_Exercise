/*
 * Lab8.c
 *
 * Created: 6/25/2022 7:59:21 PM
 * Author : Abdalla
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint-gcc.h>
#include <math.h>
#include <avr/eeprom.h>

int main(void)
{
	// check EEPROM value at location 0
	volatile float dc;
	volatile int eeprom = eeprom_read_byte((const uint8_t*) 0);
	
	if (eeprom == 255)
	{
	OCR0B = 78;									// initialize duty cycle to 0%
	eeprom_update_byte((uint8_t*) 0, (uint8_t) 230);	// update EEPROM for 10% duty cycle
	}
	
	else 
	{
		dc = (eeprom/10.0) * (2/51.0);			// calculate duty cycle of the PWM depending on the EEPROM value
		OCR0B = (uint8_t) round((78*dc)-1);	// update timer
		
		if (dc < 0.05)
		eeprom_update_byte((uint8_t*) 0, (uint8_t) 255);		// update EEPROM
		
		else
		eeprom_update_byte((uint8_t*) 0, (uint8_t) round(((dc-0.1)*10.0)*(51/2.0)));	// update EEPROM
	}

	//enable global interrupts
	sei();
	
	// initiate timer0 to generate PWM with a fix 2ms period and varying duty cycle
	TCCR0A |= (1<<WGM00) | (1<<WGM01);		// PWM mode
	TCCR0B |= 1<<WGM02;						// PWM mode
	OCR0A = 77;								// 5ms period of the PWM signal to generate 
	TIMSK0 |= (1<<OCIE0A) | (1<<OCIE0B);	// enable interrupt for compare match A&B
	
	//initialize IO pins for the LED
	DDRB |= 0x20;
		
	// enable timer
	TCCR0B |= (1<<CS02) | (1<<CS00);		// 1024 prescaler
	//eeprom_update_byte((uint8_t*) 0, (uint8_t) 255);	// update EEPROM
	while (1)
	{
	}
}

ISR (TIMER0_COMPA_vect)
{
	PORTB &= ~(1<<PORTB5);					// turn off LED
}

ISR (TIMER0_COMPB_vect)
{
	PORTB |= 1<<PORTB5;						// turn on LED
}
