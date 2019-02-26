#ifndef ACCEL_H
#define ACCEL_H

#define ACCEL_ADDR (uint32_t)(0x01D)
#define ACCEL_DATA_REG		(uint32_t)(0x01)
#define ACCEL_CTRL_REG_1	(uint32_t)(0x02A)
#define ACCEL_200_HZ_ON		(uint32_t)(0x11)
void accel_init();

void accel_read_x_y_z(int * data_buffer);

#endif
