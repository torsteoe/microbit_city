#include <stdint.h>
#include "uart.h"
#include <stdio.h>


#define GPIO ((NRF_GPIO_REGS*)0x50000000)
//Hei på deg T-bone
//kommentar fra torsteoe
//min endring på branch torsteoe-mac
//Workin my own branch over here! Wohoo!
typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

//nyttig funksjon for scanf
ssize_t _read(int fd, void *buf, size_t count){
char *str = (char *)(buf);
char letter;
do {
letter = uart_read();
} while(letter == '\0');
*str = letter;
return 1;
}

//nyttig funksjon for iprintf
ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

void gangeTall() {
	int int_1, int_2;
	printf("Skriv inn et tall: ");
	scanf("%d", &int_1);
	printf("\nSkriv inn et til tall: ");
	scanf("%d", &int_2);
	char res = ((int_1) * (int_2));
	uart_send(res);
}


void change_state(){

	iprintf("Norway has %d counties. \n\r", 18);


	int light_on = ((GPIO->IN)&(1<<15));


	if (light_on) {

		//skru lys av
		for(int i = 4; i <= 12; i++){ // hvis knapp a er trykket inn.

			GPIO->OUTSET = (1 << i);
		}
		for (int i = 13; i<=15; i++) {
			GPIO->OUTCLR = (1<< i);
		}
	} else {

		//skru lys på
		for(int i = 4; i <= 12; i++){

			GPIO->OUTCLR = (1 << i);
		}
		for (int i = 13; i<=15; i++) {
			GPIO->OUTSET = (1 << i);
		}
	}
}




int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;

	uart_init();
	gangeTall();



	while(1){

		if (uart_read() != '\0') {
			change_state();
		}

		if (!((GPIO->IN) & (1<<26))) { //hvis knapp b er trykket inn

			uart_send('B');




		}
		if (!((GPIO->IN) & (1<<17))) {

			uart_send('A');
		}


		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
