/* UNIVERSIDAD DEL VALLE DE GUATEMALA
 * File:   PROYECTO 1 - esclavo 2
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
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.

#include <stdint.h>
#include "I2C.h"
#include <xc.h>
#include "BTD_CONVERTER.h"
#include "PRINT_SERIAL.h"


//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000

unsigned char rutinas;
unsigned char bandera_ventilador;
unsigned char bandera_ventilador1;
unsigned char bandera_resistencia;
unsigned char bandera_resistencia1;
unsigned char bandera_servo; //RUTINAS
unsigned char bandera_servo1; //HABILITARLO
unsigned char velocidad_ventilador;
unsigned char contador_ventilador;
unsigned char contador_resistencia;
unsigned char contador_servo;
unsigned char bandera_general;


unsigned int humedad_temporal;
unsigned int humedad_final;

unsigned char temp1;
unsigned char temp2;
unsigned char luz1;
unsigned char luz2;

unsigned char solicitud;
unsigned char z;
unsigned char entrada;


unsigned char contador_timer;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

// INTERRUPCION

void __interrupt() isr(void) {

    if (RCIF) {// Interrupcion datos recibidos USART , no tiene uso aquí
        entrada = RCREG;
        RCREG = 0;
    }


    if (PIR1bits.SSPIF == 1) {// Interrupcion I2C

        SSPCONbits.CKP = 0;

        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)) {
            z = SSPBUF; // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0; // Clear the overflow flag
            SSPCONbits.WCOL = 0; // Clear the collision bit
            SSPCONbits.CKP = 1; // Enables SCL (Clock)
        }

        if (!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF; // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            //PIR1bits.SSPIF = 0; // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1; // Habilita entrada de pulsos de reloj SCL
            while (!SSPSTATbits.BF); // Esperar a que la recepción se complete
            solicitud = SSPBUF; // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);

            if (solicitud == 0x01) {
                bandera_general = 1;
            } else if (solicitud == 0x02) {
                bandera_general = 0;
            }
        } else if (!SSPSTATbits.D_nA && SSPSTATbits.R_nW) {
            z = SSPBUF;
            BF = 0;
            SSPBUF = 0;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while (SSPSTATbits.BF);
        }

        PIR1bits.SSPIF = 0;
    }


    // timer1

    // activamos bandera para enviar los datos cada 2 seg
    if (PIR1bits.TMR1IF) {
        contador_timer++;
        if (contador_timer > 5) {
            RD1 = RD1 ^ 1; //comprobacion que funciona


            if (bandera_resistencia) {
                contador_resistencia++;
                if (contador_resistencia > 5) {
                    bandera_resistencia1 = bandera_resistencia1 ^ 1;
                    contador_resistencia = 0;
                }
            } else {
                bandera_resistencia1 = 0;
                contador_resistencia = 0;
            }

            if (bandera_servo) {
                contador_servo++;
                if (contador_servo > 3) {
                    bandera_servo1 = bandera_servo1 ^ 1;
                    contador_servo = 0;
                }
            } else {
                bandera_servo1 = 0;
                contador_servo = 0;
            }



            contador_timer = 0;
        }

        TMR1H = 0x3B; // 1 SEG MAOMEO     
        TMR1L = 0xE0;
        PIR1bits.TMR1IF = 0;
    }


}

void main(void) {
    // CONFIGURACION INICIAL
    setup();
    velocidad_ventilador = 255;
    bandera_general = 0;
 

    while (1) {

     

        if (bandera_general) {
            bandera_ventilador = 1;
            bandera_resistencia = 1;
            bandera_servo = 1;


        } else {
            bandera_ventilador = 0;
            bandera_resistencia = 0;
            bandera_servo = 0;

        }

        enviar_letra('(');
        //enviar_letra(int_string(BTD_CENTENA(CCPR1)));
        //enviar_letra(int_string(BTD_DECIMAL(CCPR1)));
        enviar_letra(int_string(BTD_UNIDAD(bandera_ventilador)));
        enviar_letra(',');

        enviar_letra(int_string(BTD_UNIDAD(bandera_resistencia)));
        enviar_letra(int_string(BTD_UNIDAD(bandera_resistencia1)));
        enviar_letra(',');
 
        enviar_letra(int_string(BTD_UNIDAD(bandera_servo)));
        enviar_letra(int_string(BTD_UNIDAD(bandera_servo1)));
        enviar_letra(',');
        enviar_letra(int_string(BTD_CENTENA(solicitud)));
        enviar_letra(int_string(BTD_DECIMAL(solicitud)));
        enviar_letra(int_string(BTD_UNIDAD(solicitud)));

        enviar_letra(')');
        print("\n\r");


        switch (bandera_servo1) {// Se controlan los sistemas
            case(0): CCPR1 = 195;
                break;
            case(1): CCPR1 = 126;
                break;
        }
        switch (bandera_resistencia1) {// RESISTENCIA ESTARA EN PORTC BIT 0
            case(0): RD0 = 0;
                break;
            case(1): RD0 = 1;
                break;
        }// 127-250
        switch (bandera_ventilador) {
            case(0): RD2 = 0;
                break;
            case(1): RD2 = velocidad_ventilador;
                break;
        }



    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************

void setup(void) {
    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1; // 8MHz
    OSCCONbits.IRCF0 = 1;

    ANSEL = 0; // CONFIGURACION IO
    ANSELH = 0;
    TRISD = 0;
    PORTD = 0;

    TRISC1 = 1;
    TRISC2 = 1;


    // CONFIGURAR EUSART TRANSMITER Y RECEPTOR
    SPBRGH = 0; //BYTE SUPERIOR 9600 BAUD RATE
    SPBRG = 12; //BYTE INFERIOR
    BRGH = 0;
    BRG16 = 0;

    INTCONbits.GIE = 1; // HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE = 1; // HABILITAR INTERRUPCIONES PERIFERICOS
    PIE1bits.ADIE = 1; // HABILITAR INTERRUPCION DEL ADC

    TXSTAbits.SYNC = 0; // LO PONEMOS COMO ASINCRONO
    RCSTAbits.SPEN = 1; // HABILITA EL EUSART Y CONFIGURA LOS TINES TX/CK I/O COMO SALIDA
    TXSTAbits.TXEN = 1; // ACTIVA EL CIRCUITO PARA TRASMISOR DEL EUSART
    RCSTAbits.CREN = 1; // ACTIVA EL CIRCUITO PARA EL RECEPTOR DE EUSART
    //PIE1bits.TXIE = 1; //ES PARA INTERRUPCIONES TRANSMISOR
    PIE1bits.RCIE = 1; //ES PARA INTERRUPCIONES RECEPTOR  


    // PWM

    INTCONbits.GIE = 1; // HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE = 1; // HABILITAR INTERRUPCIONES PERIFERICOS


    //500 Hz con 8Mhz
    T2CON = 0b00000111;
    PR2 = 0b11111001;
    CCPR1L = 0X00;
    CCPR2L = 0X00;
    CCP2CON = 0X0F;
    CCP1CON = 0B00001100;

    // TIMER 2 para pwm
    while (PIR1bits.TMR2IF == 0); // Comenzar hasta que el segundo ciclo empiece se habilita el pwm
    TRISC1 = 0;
    TRISC2 = 0;


    //TIMER 1
    T1CONbits.T1CKPS1 = 1; //1:8
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1OSCEN = 1;
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;
    PIE1bits.TMR1IE = 1;
    TMR1H = 0x3B; // 0.2 seg    
    TMR1L = 0xE0;

    I2C_Slave_Init(0x60);
}






