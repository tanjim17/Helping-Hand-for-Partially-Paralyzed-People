#define F_CPU 1000000

#include <avr/io.h>

void UART_init() {
	UCSRA = 0;
	UCSRB = 0b00010000;
	UCSRC = 0b10000110;
	UBRRH = 0x00;
	UBRRL = 0xcf;
}

unsigned char UART_receive() {
	while((UCSRA & (1<<RXC)) == 0);
	//PORTA = ~PORTA;
	return UDR;
}


int main(void) {
	DDRA = 0xff;
	DDRB = 0xff;
	UART_init();
	PORTA = 0;
	PORTB = 1;
	while (1)
	{
		if(UART_receive() & 1) {
			PORTA = ~PORTA;
		}
	}
}

