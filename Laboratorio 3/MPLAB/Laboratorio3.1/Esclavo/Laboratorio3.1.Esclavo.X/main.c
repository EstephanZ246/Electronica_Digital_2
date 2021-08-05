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
#include "ADC_CONVERTER.h"
#include "SPI.h"


#define _XTAL_FREQ 1000000

// VARIABLES GLOBALES

unsigned int ADRESH_CANAL1;//canal 1
unsigned int ADRESH_CANAL2;//canal 2
unsigned int dato1;//canal 1
unsigned int dato2;//canal 2
unsigned int dato3;//canal 3
uint8_t Banderas; // Para cambio de canales ADC
uint8_t Banderas_SPI; // Para cambio de canales ADC

// PROTOTIPO DE FUNCIONES
void setup (void);



// INTERRUPCION
void __interrupt() isr (void)
{
    // INTERRUPCION DEL EUSART
    
   if(SSPIF == 1){
       Banderas_SPI = spiRead();
       
       if (Banderas_SPI == 1){
          spiWrite(ADRESH_CANAL1); 
       }else if (Banderas_SPI == 2){
          spiWrite(ADRESH_CANAL2);
       }
        SSPIF = 0;
    }

    // INTERRUPCION ADC
    if (ADIF == 1){
        switch(Banderas){
            case(1): 
                ADRESH_CANAL1 = ADC(0x01);
                Banderas = 2;
                ADIF = 0;// LIMPIAMOS BANDERA 
                break;
            case(2): 
                ADRESH_CANAL2 = ADC(0x00);
                Banderas = 1;
                ADIF = 0;// LIMPIAMOS BANDERAA
                break;
        }        
    }// INTERRUPCION TIMER 1
    
    }
    
void main(void){
    // CONFIGURACION INICIAL
setup();
Banderas = 1; // valores iniciales para que haga conversión
Banderas_SPI = 0;
while(1)// LOOP PRINCIPAL
{   
    ADCON0bits.GO_DONE = 1;
    //Velocidades de carro 

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
    PORTA = 0X23;// PARA ADC
    ANSEL = 0X03; // ENTRADAS PARA ADC
    ANSELH = 0X00;
    TRISA = 0X23;// PARA ADC, MOVER CARRO, LUZ DE CARRO EN FRENTE


    
    // INTERRUPCIONES
    INTCONbits.GIE = 1;// HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE= 1;// HABILITAR INTERRUPCIONES PERIFERICOS
    PIE1bits.ADIE = 1;// HABILITAR INTERRUPCION DEL ADC

    //ADC
    VCFG1 = 0; //VSS
    VCFG0 = 0; // VDD
    ADCON1bits.ADFM = 0;// JUSTIFICAMOS A LA IZQUIERDA-
    ADCON0bits.ADCS = 0b00;// AJUSTAMOS FUENTE DE RELOJ Fosc/2
    PIR1bits.ADIF = 0;// BAJAMOS BANDERA DE LA INTERRUPCION DEL ADC 
    ADCON0bits.ADON = 1;//ACTIVAMOS LAS CONVERSIONES CON EL ADON
   

    //SPI
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
           // Slave Select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}



    
    
    
      
  
    
    
    
 
    
  






   
