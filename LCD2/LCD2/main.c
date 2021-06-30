/*
 * LCD2.c
 *
 * Created: 24-Jun-21 6:27:52 PM
 * Author : Asus
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "LCD_I2C.h"


int main(void)
{
	DDRA = 0xff;
    i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
    while (1) 
    {
		lcd_cmd(0x80);
		lcd_msg("Prueba para");
		lcd_cmd(0xC3);
		lcd_msg("I2C");
		PORTA = ~PORTA;
		_delay_ms(2000);
    }
}

