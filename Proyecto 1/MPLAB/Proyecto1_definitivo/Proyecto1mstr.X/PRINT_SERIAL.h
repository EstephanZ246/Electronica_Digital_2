

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PRINT_SERIAL_H
#define	PRINT_SERIAL_H

#include <xc.h> // include processor files - each processor file is guarded.  

void print(unsigned char *palabra);
void println(unsigned char *palabra);
void enviar_letra(char letra);
int int_string(int valor);
int string_int(int valor);

#endif	/* XC_HEADER_TEMPLATE_H */

