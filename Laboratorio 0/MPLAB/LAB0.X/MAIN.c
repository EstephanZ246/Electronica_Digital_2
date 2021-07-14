 /* 
 * File:   Laboratorio8.c
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>     // LIBRERIAS
#include <stdint.h>
#define _XTAL_FREQ 125000
#define _tmr0_value 133 //133 Para 1SEG

// VARIABLES GLOBALES
uint8_t DISPLAY;
uint8_t JUGADOR1;
uint8_t JUGADOR2;
uint8_t BANDERA1;
uint8_t GANADAS1;
uint8_t GANADAS2;
uint8_t SALIDA;
uint8_t BANDERASTART;
int display[10]= {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X78,0X7F,0X67};
int contadordecada[10]= {0X00,0X01,0X02,0X04,0X08,0X10,0X20,0X40,0X80,0X00};

// PROTOTIPO DE FUNCIONES
void setup(void);

// INTERRUPCION
void __interrupt() isr (void)
{
    // INTERRUPCION PARA portb
    if (RBIF){
        if (PORTBbits.RB0 == 0){
            SALIDA = 5;
            BANDERASTART = 1;
        }
        if (PORTBbits.RB1== 0){
            if (BANDERA1 == 1){
              JUGADOR1 ++;  
            }  
        }
        if (PORTBbits.RB2== 0){
            if (BANDERA1 == 1){
              JUGADOR2 ++;  
            }
        }
        RBIF = 0;
    }
    if (T0IF ==1){// interrupcion timer 0
        if(SALIDA < 6 && SALIDA > 0){
            SALIDA --;   
        }
        else if (SALIDA == 0 && BANDERASTART == 1){
            BANDERA1 = 1;
            BANDERASTART = 0;  
        } 
        TMR0 = _tmr0_value;
        T0IF = 0;// BAJAMOS BANDERA
        } 
    }  
     
void main(void){
    // CONFIGURACION INICIAL
setup();
// VALORES INICIALES
BANDERA1 = 0;
BANDERASTART = 0;
SALIDA = 0;
JUGADOR1= 0;
JUGADOR2 = 0;
DISPLAY = 0;
GANADAS1= 0;
GANADAS2= 0;
PORTC = display[0];
while(1)// LOOP PRINCIPAL
{   

    PORTA = contadordecada[JUGADOR1]; //MOSTRAR VALORES EN CONTADORES DE CADA JUGADOR
    PORTD = contadordecada[JUGADOR2];
    PORTC = display[SALIDA]; // MOSTRAR VALORES EN DISPLAY
    if (SALIDA < 6 && SALIDA > 2){ // SEMAFORO SEGÚN DISPLAY
        PORTBbits.RB3=1; 
        PORTBbits.RB4=0;
        PORTBbits.RB5=0;
    }else if (SALIDA < 3 && SALIDA > 1){
        PORTBbits.RB3=0;
        PORTBbits.RB4=1;
        PORTBbits.RB5=0;
    }else if (SALIDA == 0 && BANDERASTART == 1){
        PORTBbits.RB3=0;
        PORTBbits.RB4=0;
        PORTBbits.RB5=1;   
    }
    if (JUGADOR1 == 8 || JUGADOR2 == 8 && BANDERA1 == 1){// RUTINA PARA VERIFICAR VALORES DE CONTADORES Y VER GANADOR 
        if (JUGADOR1 > JUGADOR2){
        GANADAS1++;    
        PORTC = display[GANADAS1];
        PORTBbits.RB6 = 1;
        __delay_ms(3000);
        JUGADOR1 = 0;
        JUGADOR2 = 0;
        PORTBbits.RB6 = 0;
        }else if (JUGADOR2 > JUGADOR1){
        GANADAS2++;  
        PORTC = display[GANADAS2];
        PORTBbits.RB7 = 1;
        __delay_ms(3000);
        JUGADOR1 = 0;
        JUGADOR2 = 0;
        PORTBbits.RB7 = 0;
        }
        
        BANDERA1 = 0;
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
    

    PORTB = 0X07;
    PORTC = 0X00;
    PORTD = 0X00;
    PORTA = 0X00;
     
    ANSEL = 0X00;
    ANSELH = 0X00;
    TRISA = 0X00;
    TRISC = 0X00;
    TRISB = 0X07;
    TRISD= 0X00;

    //ENABLE PULLUP PORTB
    OPTION_REGbits.nRBPU = 0;
    IOCB = 0X07;
    
    //CONFIGURACION DE PULLUP PORTB
    WPUB = 0X07;

    // CONFIGURAR TMR0
    OPTION_REGbits.T0CS = 0;// Configuramos (Fosc/4)
    //OPTION_REGbits.T0SE = 0;// Configuramos (Fosc/4)
    OPTION_REGbits.PSA = 0; // PSA asignamos el prescaler al Timer0
    OPTION_REGbits.PS2 = 1; // prescaler 1:256
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    TMR0 = _tmr0_value;
    
    // HABILITAR INTERRUPCIONES TMR0 Y PORTB
    INTCONbits.RBIF = 0;
    INTCONbits.T0IF = 0; // BANDERA TIMER0

    INTCONbits.RBIE = 1;
    INTCONbits.T0IE = 1;// HABILITAR INTERRUPCIONES TIMER0
    INTCONbits.GIE = 1;// HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE= 1;// HABILITAR INTERRUPCIONES PERIFERICO
    
}

 

