/* 
 * File:   BCH_CONVERTER.c
 * Author: Z9
 *
 * Created on July 20, 2021, 6:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "BCH_CONVERTER_DISPLAY.h"
/*
 * 
 */

unsigned int BCH_DISPLAY(unsigned int valor){
    unsigned int DISPLAY[16]= {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X67,0x77,0X7C,0X58,0X5E,0X79,0X71};
    return (DISPLAY[valor]);
}