/* UNIVERSIDAD DEL VALLE DE GUATEMALA
 * File:   PROYECTO 2
 * Author: ESTEPHAN PORTALES
 *
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>     // LIBRERIAS
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "PRINT_SERIAL.h"
#include "SPI.h"

#define _XTAL_FREQ 1000000
#define _tmr0_value  60//60 Para 100ms

// VARIABLES GLOBALES
uint8_t Entrada ;
uint8_t mandar_datos;
uint8_t bandera_SPI;
uint8_t pot1;
uint8_t pot2;
uint8_t dato1;
uint8_t dato2;

uint8_t bandera_recibido;
uint8_t recibido1;
uint8_t recibido2;
uint8_t recibido3;
uint8_t temporal;
uint8_t contador;
// PROTOTIPO DE FUNCIONES
void setup (void);



// INTERRUPCION
void __interrupt() isr (void)
{
    // INTERRUPCION DEL EUSART
    if (RCIF){
       Entrada =  RCREG;
       RCREG = 0; 
       switch(bandera_recibido){
           case(1):bandera_recibido = 2; recibido1 = Entrada; break;
           case(2):bandera_recibido = 3; recibido2 = Entrada; break;
           case(3):bandera_recibido = 1; recibido3 = Entrada; break;
       }
    }  
    // INTERRUPCION ADC
    

    if (PIR1bits.TMR1IF){
        if(mandar_datos == 0){
         mandar_datos = 1;   
        }
       TMR1H = 0xE6;         // 5ms  
       TMR1L = 0xD4;
       PIR1bits.TMR1IF = 0;
    }
    
    if (T0IF){// Interrupción del timer 0 para el multiplexado
        if (bandera_SPI == 1){
            //PORTCbits.RC2 = 0; 
            spiWrite(bandera_SPI);
            pot1=spiRead();
            //PORTCbits.RC2 = 1; 
            bandera_SPI = 2;
        }else if (bandera_SPI == 2){
             //PORTCbits.RC2 = 0; 
            spiWrite(bandera_SPI);
            pot2=spiRead();
            //PORTCbits.RC2 = 1; 
            bandera_SPI = 1;
        }
         TMR0 = _tmr0_value;
        T0IF = 0;

        
    }
    }
    
void main(void){
    // CONFIGURACION INICIAL
setup();
bandera_SPI = 1;
bandera_recibido = 1;
PORTCbits.RC2 = 0;
while(1)// LOOP PRINCIPAL
{   
    contador = 0;
    temporal = string_int(recibido1) *100;
    contador = contador + temporal;
    temporal = string_int(recibido2) * 10;
    contador = contador + temporal;
    temporal = string_int(recibido3);
    contador = contador + temporal;
    PORTB = contador;
    
    
dato1 = pot1*0.196;
dato2 = pot2*0.196;

    if (mandar_datos){ // AQUI MANDAMS LOS DATOS DE TEMPERATURA Y HUMEDAD A LA COMPUTADORA y mandamos datos al display
       enviar_letra('['); 
       enviar_letra(int_string(BTD_DECIMAL(dato1)));
       enviar_letra('.');
       enviar_letra(int_string(BTD_UNIDAD(dato1)));
       enviar_letra(',');
       enviar_letra(int_string(BTD_DECIMAL(dato2)));
       enviar_letra('.');
       enviar_letra(int_string(BTD_UNIDAD(dato2)));
       enviar_letra(']');
       print("\r");
       print("\n");
       mandar_datos = 0;
        }
  
}
}
void setup (void)
{
    // CONFIGURACION DE RELOJ
    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 0; // 1MHz
    OSCCONbits.IRCF0 = 0;

    //CONFIGURACION IO
    PORTB = 0X00;
    ANSEL = 0X00; // ENTRADAS PARA ADC
    ANSELH = 0X00;
    TRISB = 0X00;
    TRISC2 = 0;
    // INTERRUPCIONES
    INTCONbits.GIE = 1;// HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE= 1;// HABILITAR INTERRUPCIONES PERIFERICOS
    PIE1bits.ADIE = 1;// HABILITAR INTERRUPCION DEL ADC
    
    // CONFIGURAR EUSART TRANSMITER Y RECEPTOR

    SPBRGH = 0; //BYTE SUPERIOR 9600 BAUD RATE
    SPBRG = 25; //BYTE INFERIOR
    BRGH = 1;
    BRG16 = 1;
    
    TXSTAbits.SYNC= 0; // LO PONEMOS COMO ASINCRONO
    RCSTAbits.SPEN= 1; // HABILITA EL EUSART Y CONFIGURA LOS TINES TX/CK I/O COMO SALIDA
    TXSTAbits.TXEN= 1; // ACTIVA EL CIRCUITO PARA TRASMISOR DEL EUSART
    RCSTAbits.CREN = 1;// ACTIVA EL CIRCUITO PARA EL RECEPTOR DE EUSART
    //PIE1bits.TXIE = 1; //ES PARA INTERRUPCIONES TRANSMISOR
    PIE1bits.RCIE = 1; //ES PARA INTERRUPCIONES RECEPTOR  
    
// CONFIGURAR TMR0
    OPTION_REGbits.T0CS = 0;// Configuramos (Fosc/4)
    //OPTION_REGbits.T0SE = 0;// Configuramos (Fosc/4)
    OPTION_REGbits.PSA = 0; // PSA asignamos el prescaler al Timer0
    OPTION_REGbits.PS2 = 1; // prescaler 1:128
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 0;
    TMR0 = _tmr0_value;
    
   // TIMER1

T1CONbits.T1CKPS1 =0; // 1:2     configuración de timer 1
T1CONbits.T1CKPS0 =1;
T1CONbits.T1OSCEN =1;
T1CONbits.T1SYNC =1;
T1CONbits.TMR1CS =0;
T1CONbits.TMR1ON =1;
PIE1bits.TMR1IE = 1;
TMR1H = 0xE6;         // 50ms  
TMR1L = 0xD4;      

//SPI
PORTCbits.RC2 = 1;
spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}



    
    
    
      
  
    
    
    
 
    
  






   
