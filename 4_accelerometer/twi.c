
#include "twi.h"


void twi_init() {
	//Disable spi, 0x40003000 pluss 500
	volatile uint32_t * ptr = (uint32_t*)(0x40003500);
	*ptr = 0;





	//aktivere twi-modul på nRF med riktige signalliner

	NRF_TWI_REG->PSELSCL = (1 << 0);
	NRF_TWI_REG->PSELSDA = (1 << 30);



	//sette 100kbps overføringshastighet

	NRF_TWI_REG->FREQUENCY = 0x01980000;
}

void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
) {
	//1. Sett ADDRESS-registeret til slave_address.
	NRF_TWI_REG->ADDRESS = slave_address;

	//2. Start en skriveoperasjon.

	NRF_TWI_REG->STARTTX = 1;
	//NRF_TWI_REG->TXD = 0;

	//3. Overfør start_register til TWI-bussen.

	NRF_TWI_REG->TXD = start_register;
	/*4. Når dere har fått ACK tilbake fra slaven (som betyr at en TXDSENT-
	hendelse er blitt generert), starter dere en leseoperasjon uten å stoppe
	bussen. Dette kalles en repeated start sequence.
	*/

	while (!(NRF_TWI_REG->TXDSENT)) { }

	NRF_TWI_REG->STARTRX = 1;

	for (int i = 0; i < registers_to_read-1; i++) {
		while (!(RXDREADY)) {}
		data_buffer[i] = NRF_TWI_REG->RXD;

		while (!(NRF_TWI_REG->SUSPEND)) {}
		NRF_TWI_REG->RESUME = 1;

	}



	/*5. Les TWI-bussen (registers_to_read - 1) ganger. Dette er fordi
	dere må sende en NACK til slaven den siste gangen dere leser en byte.
	Hver verdi dere leser, dytter dere inn i data_buffer.
	186. */
	NRF_TWI_REG->STOP = 1;


	/*Til slutt stopper dere STOP-oppgaven, før dere leser busser for siste
	gang. Dette vil gjøre at nRFen genererer en NACK istedenfor en ACK,
	slik at slaven ikke sender ut flere byte på bussen.	*/

	//siste lesing;

	//stop STOP-oppgaven her:

	while (!(RXDREADY)) {}

	NRF_TWI_REG->STOP = 0;

	data_buffer[registers_to_read-1] = NRF_TWI_REG->RXD;
}
