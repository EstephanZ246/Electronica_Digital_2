/* 
 * File:   Laboratorio9.c
 * Author: ESTEPHAN PORTALES
 *
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
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


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>     // LIBRERIAS
#include "ADC_CONVERTER.h"
#include "BCH_CONVERTER_DISPLAY.h"

#define _XTAL_FREQ 125000 // velocidad  de oscilador
#define _tmr0_value 99 //99 Para 10ms

// VARIABLES GLOBALES

unsigned int Banderas; // variables y algunas banderas
unsigned int ADRESH_TEMP1; 
unsigned int Unidad;
unsigned int Decena;
unsigned int antir1;
unsigned int antir2;
//unsigned int muxeo;

// PROTOTIPO DE FUNCIONES
void setup(void);


// INTERRUPCION
void __interrupt() isr (void)
{
    // INTERRUPCION PARA ADC
    if (ADIF){        
        ADRESH_TEMP1 = ADC(0x00);// interrupcion del ADC, con librería
        ADIF = 0;
    }
    if (RBIF){// interrupcion del puerto B para los botones con antirrebote
        if (PORTBbits.RB0== 0){
            antir1 = 1;
        }else if (PORTBbits.RB0== 1 && antir1 == 1){// Este aumenta el valor del puerto
         //PORTD++;   
            asm("MOVLW 1");
            asm("ADDWF PORTD,F");
            antir1 = 0;
        }
        if (PORTBbits.RB1== 0){
            antir2 = 1;
        }else if (PORTBbits.RB1== 1 && antir2 == 1){//Este decrementa el valor del puerto
           // PORTD--;
            asm("MOVLW 1");
            asm("SUBWF PORTD,F");
            antir2 = 0;
        }
        RBIF =0;
    }

    if (T0IF){// Interrupción del timer 0 para el multiplexado
        PORTC = 0;
         if (PORTE == 0x01){
             asm("MOVLW 0X02");
             asm("MOVWF PORTE");
             PORTC = BCH_DISPLAY(ADRESH_TEMP1 & 0x0f);

         }else if (PORTE == 0x02){
             asm("MOVLW 0X01");
             asm("MOVWF PORTE");
             PORTC = BCH_DISPLAY((ADRESH_TEMP1 >> 4) & 0x0f);

         }
         TMR0 = _tmr0_value;
        T0IF = 0;

        
    }
} 
void main(void){
    // CONFIGURACION INICIAL
setup();

// VALORES INICIALES
asm("MOVLW 0X01");
asm("MOVWF PORTE");
while(1)// LOOP PRINCIPAL
{   
    ADCON0bits.GO_DONE = 1;
    __delay_us(10);

    if (ADRESH_TEMP1 > PORTD){ // Se verifica el valor de los contadores y adc para encender bandera de alarma
        PORTAbits.RA1=1;
    }else{
        PORTAbits.RA1=0;
    }
}

}
void setup (void)
{
    // CONFIGURACION DE RELOJ
    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 0; // 125KHztenemos  Hz
    OSCCONbits.IRCF0 = 1;

    //CONFIGURACION IO
    PORTA = 0X01;
    PORTC = 0X00;
    PORTD = 0X00;
    PORTE = 0X00;
    PORTB = 0X03;
    
    ANSEL = 0X01;
    ANSELH = 0X00;
    TRISB = 0X03;
    TRISC = 0X00;
    TRISA = 0X01;
    TRISD = 0X00;
    TRISE = 0X00;
    
    INTCONbits.RBIF = 0;
    INTCONbits.T0IF = 0; // BANDERA TIMER0
    
    //ENABLE PULLUP PORTB
    OPTION_REGbits.nRBPU = 0;
    IOCB = 0X03;
    
    //CONFIGURACION DE PULLUP PORTB
    WPUB = 0X03;
    
    
    // INTERRUPCIONES
    INTCONbits.GIE = 1;// HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE= 1;// HABILITAR INTERRUPCIONES PERIFERICOS
    INTCONbits.RBIE = 1;
    INTCONbits.T0IE = 1;// HABILITAR INTERRUPCIONES TIMER0
    
    
    // CONFIGURAR TMR0
    OPTION_REGbits.T0CS = 0;// Configuramos (Fosc/4)
    //OPTION_REGbits.T0SE = 0;// Configuramos (Fosc/4)
    OPTION_REGbits.PSA = 0; // PSA asignamos el prescaler al Timer0
    OPTION_REGbits.PS2 = 0; // prescaler 1:2
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 0;
    TMR0 = _tmr0_value;
    
    // HABILITAR INTERRUPCION DEL ADC
    PIE1bits.ADIE = 1;
    
    
    //CONFIGURAMOS EL CONVERSOR ADC
    ADCON0bits.CHS = 0x00;//Seleccionamos canal 10 (SEGUNDO POTENCIOMETRO)
    VCFG1 = 0;
    VCFG0 = 0;
    ADCON1bits.ADFM = 0;// JUSTIFICAMOS A LA IZQUIERDA-
    ADCON0bits.ADCS = 0b00;// AJUSTAMOS FUENTE DE RELOJ Fosc/2
    PIR1bits.ADIF = 0;// BAJAMOS BANDERA DE LA INTERRUPCION DEL ADC 
    ADCON0bits.ADON = 1;//ACTIVAMOS LAS CONVERSIONES CON EL ADON

    
}







   
