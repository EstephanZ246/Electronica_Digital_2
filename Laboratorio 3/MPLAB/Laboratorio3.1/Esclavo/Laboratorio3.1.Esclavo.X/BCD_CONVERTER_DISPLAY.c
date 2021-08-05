/* 
 * File:   BCD_CONVERTER.c
 * Author: Z9
 *
 * Created on July 20, 2021, 6:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "BCD_CONVERTER_DISPLAY.h"
/*
 * 
 */


unsigned int BCD_DISPLAY(int valor){
    unsigned int DISPLAY[10]= {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X78,0X7F,0X67};
    unsigned int conversor;
    conversor = DISPLAY[valor];
    return (conversor);
    
}
