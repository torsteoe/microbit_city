#include <stdint.h>
#include "gpio.h"
#include "twi.h"
#include "accel.h"
#include <stdio.h>
#include <stdlib.h>
#include "ubit_led_matrix.h"
#include "utility.h"
#include "uart.h"

void twi_test() {

	//uint8_t * data_buffer;


}


int main() {

	twi_init();
	uart_init();
	accel_init();
	ubit_led_matrix_init();
	int * data_buffer = (int *)malloc(3 * sizeof(int));
	//	data_buffer[0]=11;

	//kjør twi_multi_read




	while(1) {
		accel_read_x_y_z(data_buffer);
		int x_acc = data_buffer[0];
		int y_acc = data_buffer[1];
		int z_acc = data_buffer[2];


		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);


		//int x_accel = data_buffer[0];
		//int y_accel = data_buffer[1];
		//int x_dot = x_accel / 50;
		//int y_dot = - y_accel / 50;
		//ubit_led_matrix_light_only_at(x_dot, y_dot);
	}

	free(data_buffer);


	return 0;





}
