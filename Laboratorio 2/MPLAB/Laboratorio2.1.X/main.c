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
#include "PRINT_SERIAL.h"
#include "LCD.h"

#define _XTAL_FREQ 1000000

// VARIABLES GLOBALES

unsigned int ADRESH_CANAL1;//canal 1
unsigned int ADRESH_CANAL2;//canal 2
unsigned int dato1;//canal 1
unsigned int dato2;//canal 2
unsigned int dato3;//canal 3
uint8_t Banderas; // Para cambio de canales ADC
uint8_t Entrada ;
uint8_t mandar_datos;


// PROTOTIPO DE FUNCIONES
void setup (void);



// INTERRUPCION
void __interrupt() isr (void)
{
    // INTERRUPCION DEL EUSART
    if (RCIF){
       Entrada =  RCREG;
       RCREG = 0; 
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
    if (PIR1bits.TMR1IF){
        if(mandar_datos == 0){
         mandar_datos = 1;   
        }
       TMR1H = 11;           
       TMR1L = 71; 
       PIR1bits.TMR1IF = 0;
    }
    }
    
void main(void){
    // CONFIGURACION INICIAL
setup();
Banderas = 1; // valores iniciales para que haga conversión
Lcd_Init();// iniciamos displya
Lcd_Cmd(0x0f);//iniciamos cursor
Lcd_Set_Cursor(1,1);//posición inicial
Lcd_Write_String(" S1:   S2:   S3:");// Titulo de sensores
while(1)// LOOP PRINCIPAL
{   
    ADCON0bits.GO_DONE = 1;
    //Velocidades de carro 
    if(Entrada == '+'){
        asm("MOVLW 1"); // incremento de contador
        asm("ADDWF PORTB");
        Entrada = 0;
    }else if(Entrada == '-'){
        asm("MOVLW 1"); // decremento de contador
        asm("SUBWF PORTB");
        Entrada = 0;
    }
    
    dato1 = ADRESH_CANAL1*0.196;  // conversiones para mostrar 0-5V en display
    dato2 = ADRESH_CANAL2*0.196;
    dato3 = PORTB*0.196;
    
    if (mandar_datos){ // AQUI MANDAMS LOS DATOS DE TEMPERATURA Y HUMEDAD A LA COMPUTADORA y mandamos datos al display
       print("SENSOR 1: "); 

       enviar_letra(int_string(BTD_DECENA(dato1)));
       enviar_letra('.');
       enviar_letra(int_string(BTD_UNIDAD(dato1)));
       enviar_letra('V');

       Lcd_Set_Cursor(2,1);
       Lcd_Write_Char(int_string(BTD_DECENA(dato1)));
       Lcd_Set_Cursor(2,2);
       Lcd_Write_Char('.');
       Lcd_Set_Cursor(2,3);
       Lcd_Write_Char(int_string(BTD_UNIDAD(dato1)));
       Lcd_Set_Cursor(2,4);
       Lcd_Write_Char('V');
       
       
       print("  SENSOR 2: ");
       enviar_letra(int_string(BTD_DECENA(dato2)));
       enviar_letra('.');
       enviar_letra(int_string(BTD_UNIDAD(dato2)));
       enviar_letra('V');
       
       
       Lcd_Set_Cursor(2,7);
       Lcd_Write_Char(int_string(BTD_DECENA(dato2)));
       Lcd_Set_Cursor(2,8);
       Lcd_Write_Char('.');
       Lcd_Set_Cursor(2,9);
       Lcd_Write_Char(int_string(BTD_UNIDAD(dato2)));
       Lcd_Set_Cursor(2,10);
       Lcd_Write_Char('V');
       
       
       
       Lcd_Set_Cursor(2,13);
       Lcd_Write_Char(int_string(BTD_DECENA(dato3)));
       Lcd_Set_Cursor(2,14);
       Lcd_Write_Char('.');
       Lcd_Set_Cursor(2,15);
       Lcd_Write_Char(int_string(BTD_UNIDAD(dato3)));
       Lcd_Set_Cursor(2,16);
       Lcd_Write_Char('V');
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
    PORTA = 0X03;// PARA ADC
    PORTB = 0X00;
    PORTD = PORTE = 0;
    ANSEL = 0X03; // ENTRADAS PARA ADC
    ANSELH = 0X00;

    TRISA = 0X03;// PARA ADC, MOVER CARRO, LUZ DE CARRO EN FRENTE
    TRISB = 0X00;
    TRISD = 0;
    TRISE= 0;
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
    
    
    //ADC
    VCFG1 = 0; //VSS
    VCFG0 = 0; // VDD
    ADCON1bits.ADFM = 0;// JUSTIFICAMOS A LA IZQUIERDA-
    ADCON0bits.ADCS = 0b00;// AJUSTAMOS FUENTE DE RELOJ Fosc/2
    PIR1bits.ADIF = 0;// BAJAMOS BANDERA DE LA INTERRUPCION DEL ADC 
    ADCON0bits.ADON = 1;//ACTIVAMOS LAS CONVERSIONES CON EL ADON

    
   // TIMER1

T1CONbits.T1CKPS1 =1; // configuración de timer 1
T1CONbits.T1CKPS0 =1;
T1CONbits.T1OSCEN =1;
T1CONbits.T1SYNC =1;
T1CONbits.TMR1CS =0;
T1CONbits.TMR1ON =1;
PIE1bits.TMR1IE = 1;
TMR1H = 11;           
TMR1L = 71;            
}



    
    
    
      
  
    
    
    
 
    
  






   
