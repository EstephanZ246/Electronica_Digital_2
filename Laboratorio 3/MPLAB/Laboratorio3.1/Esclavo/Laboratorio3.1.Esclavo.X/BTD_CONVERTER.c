/* 
 * File:   BTD_CONVERTER.c
 * Author: Z9
 *
 * Created on July 20, 2021, 9:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "BTD_CONVERTER.h"

int BTD_CENTENA(int valor){
    int salida;
    salida = valor/100;
    return(salida);
}
int BTD_DECIMAL(int valor1){
    int temporal1;
    int salida1;
    temporal1 = valor1 % 100;
    salida1 = temporal1/10;
    return (salida1);
}
int BTD_UNIDAD(int valor2){
    int temporal2;
    int salida2;
    temporal2 = valor2 % 100;
    salida2 = temporal2 % 10;
    return (salida2);
    
}