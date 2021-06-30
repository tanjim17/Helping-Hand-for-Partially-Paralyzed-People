#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h" 

#include <math.h>
#include <stdio.h>


static volatile uint32_t pulse = 0, pulse1=0;
static volatile int i = 0, j=0;
int idx=-1, idx1=-1;

int main(void)
{
	/*unsigned short result;
	float final_result, final_result1;
	char output[100], output1[100];
	DDRD = 0b11110011;
	DDRB = 0b11111100;
	DDRC = 0xFF;
	
	GICR |= 1<<INT0;
	//GICR |= 1<<INT1;
	MCUCR |= 1<<ISC00;
	//MCUCR |= 1<<ISC10;

	sei();*/
	
	Lcd4_Init();
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Distance : ");
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("VKCHD");
	while (1)
	{
		/*PORTD |= 1<<PIND0;
		//PORTB |= 1<<PINB1;
		_delay_us(15);

		PORTD &= ~(1<<PIND0);
		//PORTB &= ~(1<<PINB1);
		
		if (idx)
		{
			final_result = pulse/58;
			
			//sprintf(output, "%0.2f", final_result);
			dtostrf(final_result, 4, 1, output);
			
			Lcd4_Set_Cursor(2,0);
			Lcd4_Write_String(output);
		}
		
		/*if (idx1)
		{
			final_result1 = pulse1/58;
			
			//sprintf(output, "%0.2f", final_result);
			dtostrf(final_result1, 4, 1, output1);
			
			//Lcd4_Set_Cursor(2,5);
			//Lcd4_Write_String("hi");
		}*/
		
		_delay_ms(50);
	}
}

/*
ISR(INT1_vect)
{
	if(j == 0)
	{
		TCCR0 = 0x01;
		j = 1;
		TCNT0 = 0;
		idx1 = 0;
	}
	else
	{
		TCCR0 = 0;
		pulse1 = TCNT0;
		TCNT0 = 0;
		j = 0;
		idx1=1;
	}
}

ISR(INT0_vect)
{
	if(i == 0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
		TCNT1=0;
		idx=0;
	}
	else
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
		idx=1;
	}
}*/