/*
 * atmega receiver.c
 *
 * Created: 7/20/2021 3:50:00 PM
 * Author : jayan
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// servo timer values
// 350 - -30
// 650 - 0
// 1000 - 30
// 1350 - 60
// 1700 - 90

// servo receiving convention
// first two bits contain 11
// C1-> -30
// C2-> 0
// C3 -> 30
// C4 -> 60
// C5 -> 90

volatile char command_mode = 0; // 0 -> no angle command found, 1 -> angle command found
volatile char angle = 0;

void UART_init()
{
	UCSRA = 0;
	UCSRB = 0b10011000;
	UCSRC = 0b10000110;
	UBRRH = 0x00;
	UBRRL = 0x33;
}

ISR(USART_RXC_vect)
{
	char command_data = UDR;	
	switch (command_data)
	{
		case (1):
			// room 1 turn on fan
			PORTA |= 0x01;
			break;
		case (2):
			// room 1 turn on light
			PORTA |= 0x02;
			break;
		case (3):
			// room 1 turn off fan
			PORTA &= ~(0x01);
			break;
		case (4):
			// room 1 turn off light
			PORTA &= ~(0x02);
			break;
		case (5):
			// room 2 turn on fan
			PORTA |= 0x04;
			break;
		case (6):
			// room 2 turn on light
			PORTA |= 0x08;
			break;
		case (7):
			// room 2 turn off fan
			PORTA &= ~(0x04);
			break;
		case (8):
			// room 2 turn off light
			PORTA &= ~(0x08);
			break;
		default:
			if ((command_data & 0xF0) == 0xC0)
			{	
				command_mode = 1;
				angle = command_data;
			}
		break;
	}	
}

void rotateServo(unsigned char servoComnd)
{
	unsigned char angle;
	angle = (servoComnd & 0x0F);
	if ((PORTA & 0x01) != 0)
	{
		if (angle == 1)
		{
			OCR1A=350; //-30 degree
			_delay_ms(500);	
		}
		else if (angle == 2)
		{
			OCR1A=650; //0 degree
			_delay_ms(500);
		}
		else if (angle == 3)
		{
			OCR1A=1000; //30 degree
			_delay_ms(500);
		}
		else if (angle == 4)
		{
			OCR1A=1350; //60 degree
			_delay_ms(500);
		}
		else if (angle == 5)
		{
			OCR1A=1700; //90 degree
			_delay_ms(500);
		}
		else if (angle==6)
		{
			OCR1A=1575; //75 degree
			_delay_ms(500);
		}
	}
	else if ((PORTA & 0x04) != 0)
	{
		if (angle == 1)
		{
			OCR1B=350; //-30 degree
			_delay_ms(500);
		}
		else if (angle == 2)
		{
			OCR1B=650; //0 degree
			_delay_ms(500);
		}
		else if (angle == 3)
		{
			OCR1B=1000; //30 degree
			_delay_ms(500);
		}
		else if (angle == 4)
		{
			OCR1B=1350; //60 degree
			_delay_ms(500);
		}
		else if (angle == 5)
		{
			OCR1B=1700; //90 degree
			_delay_ms(500);
		}
		else if (angle==6)
		{
			OCR1B=1575; //75 degree
			_delay_ms(500);
		}
	}
}

int main(void)
{
	DDRA = 0xff;
	
	// timer config
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(0<<CS11)|(1<<CS10); //PRESCALER=1 MODE 14(FAST PWM)
	
	ICR1=19999; //fPWM=50Hz (Period = 20ms Standard).
	
	DDRD|=(1<<PD4)|(1<<PD5); //PWM Pins as Out
	
	// use OCR1A for 1st servo
	// use OCR1B for 2nd servo
	
	UART_init();
	sei();
	
	while (1)
	{
		if (command_mode == 1)
		{	
			rotateServo(angle);
			command_mode = 0;
		}
	}
}