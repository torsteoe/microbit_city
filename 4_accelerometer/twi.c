
#include "twi.h"


void twi_init() {
	//Disable spi, 0x40003000 pluss 500
	volatile uint32_t * ptr = (uint32_t*)(0x40003500);
	*ptr = 0;

	//aktivere twi-modul på nRF med riktige signalliner

	TWI0->PSELSCL = 0;
	TWI0->PSELSDA = 30;

	TWI0->ENABLE = 5;

	//config gpio-pins:
	//GPIO->PIN_CNF[0] = (0);
	GPIO->PIN_CNF[0] = (6 << 8);
	GPIO->PIN_CNF[30] = (6 << 8);

	GPIO->DIRCLR |= (1<<30);
	GPIO->DIRCLR |= (1);


	//sette 100kbps overføringshastighet

	TWI0->FREQUENCY = 0x01980000;
}

void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
) {
	//1. Sett ADDRESS-registeret til slave_address.
	TWI0->ADDRESS = slave_address;

	//2. Start en skriveoperasjon.

	TWI0->STARTTX = 1;
	//TWI0->TXD = 0;

	//3. Overfør start_register til TWI-bussen.
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;

	/*4. Når dere har fått ACK tilbake fra slaven (som betyr at en TXDSENT-
	hendelse er blitt generert), starter dere en leseoperasjon uten å stoppe
	bussen. Dette kalles en repeated start sequence.
	*/



//KOMMER LYS FØR WHILE-LØKKEN, MEN IKKE ETTER.
//Vi får ikke satt TXDSENT til noe, og den blir ikke 1.

	while (!(TWI0->TXDSENT)) {

	}
	ubit_led_matrix_init();
	ubit_led_matrix_light_only_at(3,3);


	TWI0->TXDSENT = 0;





	TWI0->STARTRX = 1;

	for (int i = 0; i < registers_to_read-1; i++) {
		while (!(TWI0->RXDREADY)) {}
		TWI0->RXDREADY = 0;

		//Sette startrx kanskje????

		data_buffer[i] = TWI0->RXD;


	//	while (!(TWI0->SUSPEND)) {}
		//TWI0->RESUME = 1;

	}




	/*5. Les TWI-bussen (registers_to_read - 1) ganger. Dette er fordi
	dere må sende en NACK til slaven den siste gangen dere leser en byte.
	Hver verdi dere leser, dytter dere inn i data_buffer.
	186. */
	TWI0->STOP = 1;


	/*Til slutt stopper dere STOP-oppgaven, før dere leser busser for siste
	gang. Dette vil gjøre at nRFen genererer en NACK istedenfor en ACK,
	slik at slaven ikke sender ut flere byte på bussen.	*/

	//siste lesing;

	//stop STOP-oppgaven her:

	while (!(TWI0->RXDREADY)) {}

	//TWI0->STOP = 0;

	data_buffer[registers_to_read-1] = TWI0->RXD;
}
