#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"
#include <stdint.h>


int main() {


  // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

  //konfigurere jordingspinner til led-matrisen som output og sette de lave
  for (int i = 4; i<=12; i++) {
    GPIO->PIN_CNF[i] = 1;
    GPIO->OUTCLR = (1 << i);
  }


  //sette kanal A til Events
  GPIOTE->CONFIG[0] = ( (1) | (17<<8) );


  //sette kanal B, C og D til Tasks
  for (int i = 1; i<4; i++) {
    GPIOTE->CONFIG[i] = ( (3) |  ((i+12)<<8) | (3<<16)) ); //koble oppgavene til forsyningspinene

  }

  //konfigurere PPI


  //task 1
  PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
  PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

  //task 2
  PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
  PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

  //task 3
  PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
  PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

  while (1) {

  }





}
