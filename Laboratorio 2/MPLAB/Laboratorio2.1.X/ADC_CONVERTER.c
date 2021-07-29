/* 
 * File:   ADC_CONVERTER.c
 * Author: Z9
 *
 * Created on July 20, 2021, 6:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "ADC_CONVERTER.h"

// NOTA: Procurar definir la velocidad del reloj para el delay

unsigned int ADC(unsigned int channel){
    int salida;
    ADCON0bits.CHS = channel;
    salida = ADRESH;
    return(salida);
}

