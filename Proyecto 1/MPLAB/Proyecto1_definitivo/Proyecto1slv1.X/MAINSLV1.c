/* UNIVERSIDAD DEL VALLE DE GUATEMALA
 * File:   PROYECTO 1 - esclavo 1
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
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>     // LIBRERIAS
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "I2C.h"
#include "BTD_CONVERTER.h"
#include "OSCILADOR.h"
#include "PRINT_SERIAL.h"


#define _XTAL_FREQ 8000000
#define _tmr0_value 99 //99 Para 2ms



// VARIABLES GLOBALES
unsigned char temp1;
unsigned char temp2;
unsigned char luz1;
unsigned char luz2;
unsigned char banderas;
unsigned char z;
unsigned char solicitud;
unsigned char entrada;
unsigned char contador_timer;
unsigned char contador_dht;
unsigned char bandera_dht;
unsigned char temp_dht;
unsigned char hum_dht;


// PROTOTIPO DE FUNCIONES
void setup(void);
void Start_Signal(void);
__bit Check_Response();
__bit Read_Data(unsigned char* dht_data);



// INTERRUPCION

void __interrupt() isr(void) {
    // interrupcion del usart
    if (RCIF) {
        entrada = RCREG;
        RCREG = 0;
    }
    // interrupcion del adc
    if (ADIF == 1) {
        switch (banderas) {
            case(1):
                temp1 = ADRESH;
                ADCON0bits.CHS = 0x01; //Seleccionamos canal 10 (SEGUNDO POTENCIOMETRO)
                banderas = 2;
                ADIF = 0; // LIMPIAMOS BANDERA 
                break;
            case(2):
                temp2 = ADRESH;
                ADCON0bits.CHS = 0x02; //Seleccionamos canal 02 (PRIMER POTENCIOMETRO)
                banderas = 3;
                ADIF = 0; // LIMPIAMOS BANDERAA
                break;
            case(3):
                luz1 = ADRESH;
                ADCON0bits.CHS = 0x03; //Seleccionamos canal 03 (PRIMER POTENCIOMETRO)
                banderas = 4;
                ADIF = 0; // LIMPIAMOS BANDERAA
                break;
            case(4):
                luz2 = ADRESH;
                ADCON0bits.CHS = 0x00; //Seleccionamos canal 00 (PRIMER POTENCIOMETRO)
                banderas = 1;
                ADIF = 0; // LIMPIAMOS BANDERAA
                break;
        }
    }

    // Interrupcion del i2c
    if (PIR1bits.SSPIF == 1) {

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

        } else if (!SSPSTATbits.D_nA && SSPSTATbits.R_nW) {
            z = SSPBUF;
            BF = 0;
            // SSPBUF = PORTB;

            switch (solicitud) { // se mandan valores según la petición 
                case(0b10000000): SSPBUF = temp1;
                    break;
                case(0b01000000): SSPBUF = temp2;
                    break;
                case(0b11000000): SSPBUF = luz1;
                    break;
                case(0b00100000): SSPBUF = luz2;
                    break;

            }

            SSPCONbits.CKP = 1;
            __delay_us(250);
            while (SSPSTATbits.BF);
        }

        PIR1bits.SSPIF = 0;
    }

    if (T0IF) {// Interrupcion de Timer0
        contador_timer++;
        if (contador_timer > 50) {
            RD1 = RD1 ^ 1;
            contador_dht++;

            if (contador_dht > 3) {
                /// cambiar a 1
                bandera_dht = 0;
            }
            contador_timer = 0;
        }


        TMR0 = _tmr0_value;
        T0IF = 0; // BAJAMOS BANDERA
    }

}

void main(void) {
    // CONFIGURACION INICIAL
    setup();

    //Valores iniciales
    banderas = 1;
    ADCON0bits.CHS = 0x00;
    temp_dht = 0;
    hum_dht = 0;

    while (1)// LOOP PRINCIPAL
    {


        //__delay_us(10);
        ADCON0bits.GO_DONE = 1;
        enviar_letra('(');
        enviar_letra(int_string(BTD_CENTENA(temp1)));
        enviar_letra(int_string(BTD_DECIMAL(temp1)));
        enviar_letra(int_string(BTD_UNIDAD(temp1)));
        enviar_letra(',');
        enviar_letra(int_string(BTD_CENTENA(temp2)));
        enviar_letra(int_string(BTD_DECIMAL(temp2)));
        enviar_letra(int_string(BTD_UNIDAD(temp2)));
        enviar_letra(',');
        enviar_letra(int_string(BTD_CENTENA(luz1)));
        enviar_letra(int_string(BTD_DECIMAL(luz1)));
        enviar_letra(int_string(BTD_UNIDAD(luz1)));
        enviar_letra(',');
        enviar_letra(int_string(BTD_CENTENA(luz2)));
        enviar_letra(int_string(BTD_DECIMAL(luz2)));
        enviar_letra(int_string(BTD_UNIDAD(luz2)));
        enviar_letra(',');
        enviar_letra(Temperature[0]); //dht
        enviar_letra(Temperature[1]);
        enviar_letra(Temperature[2]);
        enviar_letra(Temperature[3]);
        enviar_letra(',');
        enviar_letra(Humidity[0]); //dht
        enviar_letra(Humidity[1]);
        enviar_letra(Humidity[2]);
        enviar_letra(Humidity[3]);
        enviar_letra(')');
        print("\n\r");

        
}
}

void setup(void) {
    // Velocidad de reloj

    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;

    //Configuracion de puertos (Sensores)
    TRISA = 0x0F;
    PORTA = 0X0F;
    ANSEL = 0X0F;
    ANSELH = 0X00;
    TRISD = 0;
    PORTD = 0x00;

    //Interrupciones
    INTCONbits.GIE = 1; // HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE = 1; // HABILITAR INTERRUPCIONES PERIFERICOS
    PIE1bits.ADIE = 1; // HABILITAR INTERRUPCION DEL ADC

    //ADC
    VCFG1 = 0; //VSS
    VCFG0 = 0; // VDD
    ADCON1bits.ADFM = 0; // JUSTIFICAMOS A LA IZQUIERDA-
    ADCON0bits.ADCS = 0b00; // AJUSTAMOS FUENTE DE RELOJ Fosc/2
    PIR1bits.ADIF = 0; // BAJAMOS BANDERA DE LA INTERRUPCION DEL ADC 
    ADCON0bits.ADON = 1; //ACTIVAMOS LAS CONVERSIONES CON EL ADON


    // CONFIGURAR EUSART TRANSMITER Y RECEPTOR
    SPBRGH = 0; //BYTE SUPERIOR 9600 BAUD RATE
    SPBRG = 12; //BYTE INFERIOR
    BRGH = 0;
    BRG16 = 0;

    TXSTAbits.SYNC = 0; // LO PONEMOS COMO ASINCRONO
    RCSTAbits.SPEN = 1; // HABILITA EL EUSART Y CONFIGURA LOS TINES TX/CK I/O COMO SALIDA
    TXSTAbits.TXEN = 1; // ACTIVA EL CIRCUITO PARA TRASMISOR DEL EUSART
    RCSTAbits.CREN = 1; // ACTIVA EL CIRCUITO PARA EL RECEPTOR DE EUSART
    //PIE1bits.TXIE = 1; //ES PARA INTERRUPCIONES TRANSMISOR
    PIE1bits.RCIE = 1; //ES PARA INTERRUPCIONES RECEPTOR  

   

    // CONFIGURAR TMR0
    OPTION_REGbits.T0CS = 0; // Configuramos (Fosc/4)
    OPTION_REGbits.T0SE = 0; // Configuramos (Fosc/4)
    OPTION_REGbits.PSA = 0; // PSA asignamos el prescaler al Timer0
    OPTION_REGbits.PS2 = 1; // prescaler 1:256
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    TMR0 = _tmr0_value;


    I2C_Slave_Init(0x50);


}















