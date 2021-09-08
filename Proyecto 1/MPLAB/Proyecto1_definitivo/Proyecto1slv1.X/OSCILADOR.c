/* 
 * File:   OSCILADOR.c
 * Author: Z9
 *
 * Created on August 2, 2021, 10:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "OSCILADOR.h"

/*
 * 
 */

void Osc_vel(unsigned char velocidad){
    OSCCONbits.SCS = 1;
    
    if (velocidad & 0b001){
    OSCCONbits.IRCF0 = 1;
    }else {
    OSCCONbits.IRCF0 = 0;  
    }
    if (velocidad & 0b010){        
    OSCCONbits.IRCF1 = 1; 
    }else{
    OSCCONbits.IRCF1 = 0; 
    }
    
    if (velocidad & 0b100){
    OSCCONbits.IRCF2 = 1;  
    }else{
    OSCCONbits.IRCF2 = 0;
    }
}
