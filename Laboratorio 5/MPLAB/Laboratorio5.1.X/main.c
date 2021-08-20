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
#include "PRINT_SERIAL.h"
#include "BTD_CONVERTER.h"

#define _XTAL_FREQ 1000000

// VARIABLES GLOBALES
unsigned char contador1;
unsigned char contador_usart;
unsigned char BANDERASTART1;
unsigned char BANDERASTART;
unsigned char Entrada;
unsigned char bandera_recibido;
unsigned char recibido1;
unsigned char recibido2;
unsigned char recibido3;
unsigned char mandar_datos;
unsigned char contador;
unsigned char temporal;
unsigned char bandera1;
// PROTOTIPO DE FUNCIONES
void setup (void);




// INTERRUPCION
void __interrupt() isr (void)
{
    // INTERRUPCION DEL EUSART
    if (RCIF){ // recibimos los datos del usart para desplegarlo en puerto
       Entrada =  RCREG;
       RCREG = 0; 
       switch(bandera_recibido){
           case(1):bandera_recibido = 2; recibido1 = Entrada; break;
           case(2):bandera_recibido = 3; recibido2 = Entrada; break;
           case(3):bandera_recibido = 1; recibido3 = Entrada;  bandera1 = 1 ; break;
           
       }
    }  
    // timer1
    
// activamos bandera para enviar los datos cada 2 seg
    if (PIR1bits.TMR1IF){
        if(mandar_datos == 0){
         mandar_datos = 1;   
        }
       RB7 = 1;
       TMR1H = 0x0;         // 2seg  
       TMR1L = 0x0;
       PIR1bits.TMR1IF = 0;
    } 
    // PORTB
    
    if (RBIF){// botones para aumentar y decrementar los contadores
       if (PORTBbits.RB0 == 0){
            BANDERASTART = 1;
        }else if (PORTBbits.RB0 == 1 && BANDERASTART == 1){
            contador1++;
            BANDERASTART = 0;
        }
        
        
        if (PORTBbits.RB1== 0){
            BANDERASTART1 = 1; 
        }
        if (PORTBbits.RB1== 1 && BANDERASTART1 == 1){
            contador1--;
            BANDERASTART1 = 0;
        }
      RBIF = 0;
    
    }
}
    
void main(void){
    // CONFIGURACION INICIAL
setup();
bandera_recibido = 1;
while(1)// LOOP PRINCIPAL
{   
    if (mandar_datos){
    enviar_letra(int_string(BTD_CENTENA(contador1)));
    enviar_letra(int_string(BTD_DECIMAL(contador1)));
    enviar_letra(int_string(BTD_UNIDAD(contador1)));
    mandar_datos = 0;
    }
    if (bandera1){
    contador = 0;
    temporal = string_int(recibido1) *100;
    contador = contador + temporal;
    temporal = string_int(recibido2) * 10;
    contador = contador + temporal;
    temporal = string_int(recibido3);
    contador = contador + temporal;
    PORTD = contador;
    bandera1 = 0;
    RB7=0;
    }
    PORTA = contador1; 
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
    PORTA = 0X00;// PARA CONTADOR USART
    PORTB = 0X03; // PARA BOTONES
    PORTD = 0X00;// PARA CONTADOR BOTONES

    
    ANSEL = 0X00; // ENTRADAS PARA ADC
    ANSELH = 0X00;
    TRISA = 0X00;// PARA ADC, MOVER CARRO, LUZ DE CARRO EN FRENTE
    TRISB = 0X03;
    TRISD = 0X00;

       //ENABLE PULLUP PORTB
    OPTION_REGbits.nRBPU = 0;
    IOCB = 0X03;
    
    //CONFIGURACION DE PULLUP PORTB
    WPUB = 0X03;
    
    // INTERRUPCIONES
    INTCONbits.GIE = 1;// HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE= 1;// HABILITAR INTERRUPCIONES PERIFERICOS
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
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
    
    T1CONbits.T1CKPS1 =1; // 1:2     configuración de timer 1
    T1CONbits.T1CKPS0 =1;
    T1CONbits.T1OSCEN =1;
    T1CONbits.T1SYNC =1;
    T1CONbits.TMR1CS =0;
    T1CONbits.TMR1ON =1;
    PIE1bits.TMR1IE = 1;
    TMR1H = 0x0;         //2 seg 
    TMR1L = 0x0;      
    
    
}




    
    
    
      
  
    
    
    
 
    
  






   
