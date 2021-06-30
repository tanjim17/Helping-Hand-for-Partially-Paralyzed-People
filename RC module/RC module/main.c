#define F_CPU 1000000 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void UART_init() {
	UCSRA = 0;
	UCSRB = 0b00001000;
	UCSRC = 0b10000110;
	UBRRH = 0x00;
	UBRRL = 0xcf;
}

void UART_send(unsigned char data) {
	while((UCSRA & (1<<UDRE)) == 0);
	UDR = data;
}

/*ISR(INT2_vect) {
	UART_send(1);
	PORTA = ~PORTA;
}*/

int main(void) {
    DDRA = 0xff;
	UART_init();
	GICR = 1<<INT2;
	MCUCSR = 1<<ISC2;
	sei();
	PORTA = 0;
    while (1) 
    {	
		//PORTA = ~PORTA;
		UART_send(1);
		PORTA = ~PORTA;
		_delay_ms(2000);
    }
}

