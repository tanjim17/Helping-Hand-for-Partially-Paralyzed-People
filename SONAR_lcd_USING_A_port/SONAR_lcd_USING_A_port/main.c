
#define F_CPU 8000000UL

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"

#define  Trigger_pin	PA0	/* Trigger pin */

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;		/* Increment Timer Overflow count */
}

int main(void)
{
	char string[10];
	long count;
	double distance;
	
	DDRA = 0x01;			/* Make trigger pin as output */
	PORTD = 0xFF;			/* Turn on Pull-up */
	
	
	Lcd4_Init();
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("hello bondhu ra");
	
	sei();					/* Enable global interrupt */
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;				/* Set all bit to zero Normal operation */

	while(1)
	{

		PORTA |= (1 << Trigger_pin);/* Give 10us trigger pulse on trig. pin to HC-SR04 */
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;			/* Clear Timer counter */
		TCCR1B = 0x41;		/* Setting for capture rising edge, No pre-scaler*/
		TIFR = 1<<ICF1;		/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;		/* Clear Timer Overflow flag */

		/*Calculate width of Echo by Input Capture (ICP) on PortD PD6 */
		
		while ((TIFR & (1 << ICF1)) == 0);	/* Wait for rising edge */
		TCNT1 = 0;			/* Clear Timer counter */
		TCCR1B = 0x01;		/* Setting for capture falling edge, No pre-scaler */
		TIFR = 1<<ICF1;		/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;		/* Clear Timer Overflow flag */
		TimerOverflow = 0;	/* Clear Timer overflow count */

		while ((TIFR & (1 << ICF1)) == 0); /* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow);	/* Take value of capture register */
		/* 8MHz Timer freq, sound speed =343 m/s, calculation mentioned in doc. */
		distance = (double)count / 466.47;

		dtostrf(distance, 2, 2, string);/* Convert distance into string */
		strcat(string, " cm   ");
		//LCD_String_xy(2, 0, "Dist = ");
		//LCD_String_xy(2, 7, string);	/* Print distance on LDC16x2 */
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String(string);
		_delay_ms(200);
	}
}


