/* 
 * File:   IO_CONFIG.c
 * Author: Z9
 *
 * Created on August 2, 2021, 10:18 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "IO_CONFIG.h"
/*
 * 
 */


void PORT_CONFIG(unsigned char PUERTOA, unsigned char PUERTOB ,unsigned char PUERTOC ,unsigned char PUERTOD ,unsigned char PUERTOE ){
    
    PORTA = PUERTOA;
    PORTB = PUERTOB;
    PORTC = PUERTOC;
    PORTD = PUERTOD;
    PORTE = PUERTOE; 
    
    TRISA = PUERTOA;
    TRISB = PUERTOB;
    TRISC = PUERTOC;
    TRISD = PUERTOD;
    TRISE = PUERTOE;
}

void PULLUP(unsigned char pines){
    OPTION_REGbits.nRBPU = 0;
    IOCB = pines;
    WPUB = pines;
}