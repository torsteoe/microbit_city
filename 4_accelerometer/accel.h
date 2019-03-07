#ifndef ACCEL_H
#define ACCEL_H

#define ACCEL_ADDR (uint8_t)(0x19)
#define ACCEL_DATA_REG		(uint32_t)(0x28) //kan være 28, studass
#define ACCEL_CTRL_REG_1	(uint32_t)(0x20)
#define ODR0                4
#define ACCEL_200_HZ_ON		(uint32_t)(0x6<<ODR0)
void accel_init();

void accel_read_x_y_z(int * data_buffer);

#endif
