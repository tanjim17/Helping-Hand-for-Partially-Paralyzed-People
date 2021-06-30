// Code for LCD Interfacing with ATmega32 AVR microcontroller

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
// #include "ultrasonic.h"


#define RS 6
#define E  5

void send_a_command (unsigned char command);
void send_a_character(unsigned char character);

/*

uint8_t sensor_working=0;
uint8_t rising_edge=0;
uint32_t timer_counter=0;
uint32_t distance;
uint8_t distance_str[10];

void ultrasonic_init(void){

	TRIGER_DDR|=(1<<TRIGER);
	ECHO_DDR&=~(1<<ECHO);
	ECHO_PULLUP|=(1<<ECHO);
	enable_ex_interrupt();
	timer0_init();
	return;
}

void enable_ex_interrupt(void){

	MCUCR |= (1<<ISC10);		// Trigger INT1 on any logic change.
	GICR  |= (1<<INT1);			// Enable INT1 interrupts.

	return;
}

void ultra_triger(void){
	if(!sensor_working){
		TRIGER_PORT|=(1<<TRIGER);
		_delay_us(15);
		TRIGER_PORT&=~(1<<TRIGER);
		sensor_working=1;
	}
}

ISR(INT1_vect){
	if(sensor_working==1){
		if(rising_edge==0){
			TCNT0=0x00;
			rising_edge=1;
			timer_counter=0;
		}
		else{
			distance=(timer_counter*256+TCNT0)/466;
			send_a_command(0x01);// sending all clear command
			send_a_command(0x38);// 16*2 line LCD
			send_a_command(0x0E);// screen and cursor ON
			itoa(distance,distance_str,10);
			strcat(distance_str, " cm ");
			lcd_write_word(distance_str);
			_delay_ms(40);
			timer_counter=0;
			rising_edge=0;
		}
	}}

	ISR(TIMER0_OVF_vect){
		timer_counter++;
		if(timer_counter >730){
			TCNT0=0x00;
			sensor_working=0;
			rising_edge=0;
			timer_counter=0;
		}
	}

void lcd_write_word(uint8_t word[20])
{
	int i=0;
	while(word[i]!='\0')
	{
		send_a_character(word[i]);
		i++;
	}
}

*/

int main(void)
{
	DDRA = 0xFF;
	DDRD = 0xFF;
	_delay_ms(50);
	send_a_command(0x01);// sending all clear command
	send_a_command(0x38);// 16*2 line LCD
	send_a_command(0x0E);// screen and cursor ON
	
	/*
	ultrasonic_init();
	sei();
	
	send_a_character (0x44); // ASCII(American Standard Code for Information Interchange) code for 'D'
	send_a_character (0x49); // ASCII(American Standard Code for Information Interchange) code for 'I'
	send_a_character (0x4C); // ASCII(American Standard Code for Information Interchange) code for 'L'
	send_a_character (0x49); // ASCII(American Standard Code for Information Interchange) code for 'I'
	send_a_character (0x50); // ASCII(American Standard Code for Information Interchange) code for 'P'
	*/
	while(1) {
		
		send_a_command(0x01);// sending all clear command
		send_a_command(0x38);// 16*2 line LCD
		send_a_command(0x0E);// screen and cursor ON
		send_a_character (0x44); // ASCII(American Standard Code for Information Interchange) code for 'D'
		send_a_character (0x49); // ASCII(American Standard Code for Information Interchange) code for 'I'
		send_a_character (0x4C); // ASCII(American Standard Code for Information Interchange) code for 'L'
		send_a_character (0x49); // ASCII(American Standard Code for Information Interchange) code for 'I'
		send_a_character (0x50); // ASCII(American Standard Code for Information Interchange) code for 'P'
		/*
		ultra_triger();
		_delay_ms(15);*/
	}
	
	
}

void send_a_command (unsigned char command)
{
	PORTA=command;
	PORTD&= ~(1<<RS);
	PORTD|= (1<<E);
	_delay_ms(50);
	PORTD&= ~(1<<E);
	PORTA =0;
}

void send_a_character (unsigned char character)
{
	PORTA=character;
	PORTD|= (1<<RS);
	PORTD|= (1<<E);
	_delay_ms(50);
	PORTD&= ~(1<<E);
	PORTA =0;
}