/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IO_CONFIG
#define	IO_CONFIG

#include <xc.h> // include processor files - each processor file is guarded.  

void PORT_CONFIG(unsigned char PUERTOA , unsigned char PUERTOB ,unsigned char PUERTOC ,unsigned char PUERTOD ,unsigned char PUERTOE );
void PULLUP(unsigned char pines);


#endif	/* XC_HEADER_TEMPLATE_H */

