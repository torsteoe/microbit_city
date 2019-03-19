#include <stdint.h>
#include "accel.h"
#include "twi.h"
#include "utility.h"
#include "uart.h"
#include <stdlib.h>

void accel_init(){
	uint8_t data = (ACCEL_200_HZ_ON | 0b1111);
	twi_multi_write(ACCEL_ADDR, ACCEL_CTRL_REG_1, 1, &data);
/*
	uint8_t * data_buffer2 = (uint8_t *)malloc(8*sizeof(uint8_t));
	twi_multi_read(
		ACCEL_ADDR,
	 	ACCEL_CTRL_REG_1, //slave_address =who_am_i
		1,
		data_buffer2
	);

	utility_print(&uart_send, "data: %d", data_buffer2[0]);
*/



}

void accel_read_x_y_z(int * data_buffer){
	uint8_t raw_data[6] = {0, 0, 0, 0, 0, 0};
	twi_multi_read(ACCEL_ADDR, ACCEL_DATA_REG, 6, raw_data);

	int8_t x_accel, y_accel, z_accel;

	// MSB and LSB are in 2s complement,
	// but LSB only contains two bits
	x_accel = raw_data[0];
	//x_accel = -(x_accel >> 10);
	y_accel = raw_data[2];
	//y_accel = -(y_accel >> 10);
	z_accel = raw_data[4];
	//z_accel = -(z_accel >> 10);

	data_buffer[0] = (int)x_accel;
	data_buffer[1] = (int)y_accel;
	data_buffer[2] = (int)z_accel;
}
