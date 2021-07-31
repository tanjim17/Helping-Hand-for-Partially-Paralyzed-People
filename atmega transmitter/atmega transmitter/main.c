/*
 * atmega transmitter.c
 *
 * Created: 7/6/2021 7:01:27 PM
 * Author : jayanta
 */ 

#ifndef F_CPU
#define F_CPU 1000000
#endif 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#define BAUDRATE 1200
#define UBRRVAL ((F_CPU / (BAUDRATE * 16UL)) - 1)

volatile char c, ch, comm_bits;
volatile char message[16];
volatile int size = -1;
volatile char msgFlag = 0;

// RRL - Turn on fan
// LRL - Turn on light
// RLR - Need Help
// RLL - Call Medics
// LRR - Call Maid
// LLL - Turn Off Fan
// LLR - Turn Off Light

void UART_init()
{
	UCSRA = 0;
	UCSRB = 0b10011000;
	UCSRC = 0b10000110;
	UBRRH = 0x00;
	UBRRL = 0x33;
}

void UART_send(unsigned char data)
{
	while((UCSRA & (1<<UDRE)) == 0);
	UDR = data;
}

void command_select()
{
	switch (ch)
	{
		case(1):
			UART_send(1);
			break;
		case(5):
			UART_send(5);
			break;
		case(2):
			UART_send(2);
			break;
		case(3):
			UART_send(3);
			break;
		case(4):
			UART_send(4);
			break;
		case(7):
			UART_send(7);
			break;
		case (6):
			UART_send(6);
			break;
	}
}

void execute_command()
{
	command_select();
	ch = 0;
	comm_bits = 0;
	_delay_ms(1000);
}

ISR(INT0_vect)
{
	comm_bits = comm_bits + 1;
	ch = ch << 1;
	PORTA |= 0x02;
	_delay_ms(100);
	PORTA &= ~(0x02);
}

ISR(INT1_vect)
{
	comm_bits = comm_bits + 1;
	ch = (ch<<1) + 1;
	PORTA |= 0x04;
	_delay_ms(100);
	PORTA &= ~(0x04);
}

int main(void)
{
	DDRA = 0xff;
	PORTA = 0x00;

	GICR = (1<<INT0);
	GICR |= (1<<INT1);
	MCUCR = (1<<ISC01);
	MCUCR |= (1<<ISC11);
	
	UART_init();	
	comm_bits = 0;
	sei();
	
	while (1)
	{
		if (comm_bits == 3 && ch !=0)
		{
			PORTA = PORTA ^ 0x01;
			execute_command();
		}
		else if (comm_bits == 3 && ch == 0)
		{
			comm_bits = 0;
			ch  =0;
		}
	}
}