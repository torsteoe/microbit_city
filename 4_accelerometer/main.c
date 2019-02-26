#include <stdint.h>
#include "gpio.h"
#include "twi.h"
#include "accel.h"
#include <stdio.h>
#include <stdlib.h>
#include "ubit_led_matrix.h"
void twi_test() {

	uint8_t * data_buffer;
	data_buffer = (uint8_t *)malloc(8*sizeof(uint8_t));


	//kjør twi_multi_read
	twi_multi_read(
		/* slave address*/ ACCEL_ADDR,
		/* start_register*/0x0D,
		/*num of registers*/ 1,
		/*skriver til: */ data_buffer
	);


	if (*data_buffer == 0x5A) {




	}

	free(data_buffer);


}





int main() {

	twi_init();

	twi_test();


	return 0;





}
