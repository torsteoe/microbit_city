#include "uart.h"
#include "gpio.h"


void uart_init() {
  UART->BAUDRATE = 0x00275000; //Sette baudrate til 9600;

  //UART->NCTS = 1; // disable CTS
  UART->PSELRTS = 0xFFFFFFFF; //disable rts
  UART->PSELCTS = 0xFFFFFFFF;

  UART->ENABLE = 1 << 2; // enable uart
  UART->STARTRX = 1; //starte å ta imot meldinger

  //Cofigure pins for input and output
  GPIO->PIN_CNF[24] = 1; //transmit
	GPIO->PIN_CNF[25] = 0; //reception

  //sette uart pins
  UART->PSELTXD = 24;
  UART->PSELRXD = 25;

}

void uart_send(char letter) {

  UART->STARTTX = 1;
  UART->TXD = letter;
  while (!(UART->TXDRDY)) {

  }
  UART->TXDRDY = 0;
  UART->STOPTX = 1;

}

char uart_read() {
  UART->STARTRX = 1;
  char letter;
  if (UART->RXDRDY) {
    UART->RXDRDY=0;
    letter= UART->RXD;
    return letter;
  } else {
    return '\0';
  }
}
