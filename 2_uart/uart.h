#include <stdint.h>
#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
	//Task
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX
	volatile uint32_t STOPTX;
	volatile uint32_t reserved_0[3];
	volatile uint32_t SUSPEND; 
	//Events
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t reserved_1[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t reserved_2[1];
	volatile uint32_t ERROR;
	volatile uint32_t reserved_3[7];
	volatile uint32_t RXTO;
	
	volatile uint32_t reserved_4[110];
	//Registers
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t reserved_5[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t reserved_6[31];

	volatile uint32_t ENABLE;
	volatile uint32_t reserved_7[1];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;

	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t reserved_8[1];
	volatile uint32_t BAUDRATE;
	volatile uint32_t reserved_9[17];
	volatile uint32_t CONFIG;



} NRF_UART_REG;

void uart_init();
void uart_send(char letter);
void uart_read();

