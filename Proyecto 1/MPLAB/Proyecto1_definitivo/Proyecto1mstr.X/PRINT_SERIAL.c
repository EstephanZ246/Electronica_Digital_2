/* 
 * File:   PRINT_SERIAL.c
 * Author: Z9
 *
 * Created on July 28, 2021, 12:42 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "PRINT_SERIAL.h"
/*
 * 
 */

void print(unsigned char *palabra){ // FUNCION IMPRIMIR PALABRA SIN "ENTER"
    while((*palabra) != '\0'){
        while(!TXIF);
        TXREG = (*palabra);
        *palabra++;
          
  }
}
void println(unsigned char *palabra){//FUNCION IMPRIMIR PALABRA CON "ENTER"
    while((*palabra) != '\0'){
        while(!TXIF);
        TXREG = (*palabra);
        *palabra++;
          
  }
    enviar_letra('\r');
}

void enviar_letra(char letra){// ENVIAR SOLO LETRA
    while(!TXIF);
    TXREG = letra;   
}

int int_string(int valor){ // PARA PODER MANDAR EL NUMERO A LA PC, PORQUE SI SOLO LE MANDAMOS EL NUMERO, 
                             // QUE NO SEA STRING PUEDE MANDAR ALGO NADA QUE VER
    switch (valor){
        case(0): return('0'); break;
        case(1): return('1'); break;
        case(2): return('2'); break;
        case(3): return('3'); break;
        case(4): return('4'); break;
        case(5): return('5'); break;
        case(6): return('6'); break;
        case(7): return('7'); break;
        case(8): return('8'); break;
        case(9): return('9'); break; 
    }
}

int string_int(int valor){ // PARA PODER MANDAR EL NUMERO A LA PC, PORQUE SI SOLO LE MANDAMOS EL NUMERO, 
                             // QUE NO SEA STRING PUEDE MANDAR ALGO NADA QUE VER
    switch (valor){
        case('0'): return(0); break;
        case('1'): return(1); break;
        case('2'): return(2); break;
        case('3'): return(3); break;
        case('4'): return(4); break;
        case('5'): return(5); break;
        case('6'): return(6); break;
        case('7'): return(7); break;
        case('8'): return(8); break;
        case('9'): return(9); break; 
    }
}



