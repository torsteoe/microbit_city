#define TWI0 ((NRF_TWI_REG*)0x40003000)
#include <stdint.h>
#include "gpio.h"
#include "ubit_led_matrix.h"

typedef struct {
	volatile uint32_t STARTRX;
	volatile uint32_t RESERVED[1];
	volatile uint32_t STARTTX;
	volatile uint32_t RESERVED_1[2];
	volatile uint32_t STOP;
	volatile uint32_t RESERVED_2[1];
	volatile uint32_t SUSPEND;
	volatile uint32_t RESUME;
	volatile uint32_t RESERVED_3[56];
	volatile uint32_t STOPPED;
	volatile uint32_t RXDREADY;
	volatile uint32_t RESERVED_4[4];
	volatile uint32_t TXDSENT;
	volatile uint32_t RESERVED_5[1];
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED_6[4];
	volatile uint32_t BB;
	volatile uint32_t RESERVED_7[49];
	volatile uint32_t SHORTS;
	volatile uint32_t RESERVED_8[63];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED_9[110];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED_10[14];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED_11[1];
	volatile uint32_t PSELSCL;
	volatile uint32_t PSELSDA;
	volatile uint32_t RESERVED_12[2];
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED_13[1];
	volatile uint32_t FREQUENCY;
	volatile uint32_t RESERVED_14[24];
	volatile uint32_t ADDRESS;
} NRF_TWI_REG;


void twi_init();
void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
);
void twi_multi_write(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_write,
	uint8_t * data_buffer
);
