/* UNIVERSIDAD DEL VALLE DE GUATEMALA
 * File:   PROYECTO 1 - Maestro 1
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
// Use project enums instead of #define for ON and OFF.
#include <xc.h>     // LIBRERIAS
#include <stdint.h>

///#include "LCD.h"
#include "PRINT_SERIAL.h"
#include "I2C.h"
#include "LCD.h"
#include "BTD_CONVERTER.h"


#define _XTAL_FREQ 8000000



// VARIABLES GLOBALES

unsigned char Entrada;

//variables finales de sensores
unsigned char temperatura1;
unsigned char temperatura2;
unsigned char luz1;
unsigned char luz2;

//valores temporales de sensores para hacer conversiones
unsigned char temp_temp1;
unsigned char temp_temp2;
unsigned char temp_luz1;
unsigned char temp_luz2;

//banderas y contadores de timer1
unsigned char contador_lcd;
unsigned char bandera_lcd;
unsigned char bandera_lcd1;
unsigned char bandera_serial;
unsigned char contador_serial;
unsigned char bandera_ventilador;
unsigned char bandera_resistencia;
unsigned char bandera_servo;
unsigned char bandera_extra;
unsigned char contador_info;
unsigned char bandera_info;
unsigned char contador_timer1;
unsigned char BMP1;
unsigned char BMP2;
unsigned char temp_bmp;


//valores nominales de temp
unsigned char temp_nom = 28;

// PROTOTIPO DE FUNCIONES
void setup(void);

// INTERRUPCION

void __interrupt() isr(void) {


    // INTERRUPCION DEL EUSART
    if (RCIF) {
        Entrada = RCREG;
        RCREG = 0;

    }

    // INTERRUPCION TIMER 1
    if (PIR1bits.TMR1IF) {
        contador_timer1++;

        if (contador_timer1 >= 5) {

            contador_serial++;
            contador_lcd++;
            contador_info++;
            RB1 = RB1 ^ 1; //verificar que funciona

            if (contador_lcd >= 2) {
                bandera_lcd1 = 1;

                contador_lcd = 0;
            }
            if (contador_serial >= 10) {//valor normal 10
                bandera_serial = 1;
                contador_serial = 0;
            }


            bandera_info++;

            if (contador_info > 2) {
                bandera_info = 1;
                contador_info = 0;
            }

            contador_timer1 = 0;
        }

        TMR1H = 0x3B; // 0.2 seg    
        TMR1L = 0xE0;
        PIR1bits.TMR1IF = 0;
    }
}

void main(void) {
    // CONFIGURACION INICIAL
    setup();
    // Valores iniciales
    contador_lcd = 0;
    contador_serial = 0;
    bandera_lcd = 0;
    bandera_serial = 0;
    //bandera_info = 0;
    contador_info = 0;


    Lcd_Init(); // iniciamos display
    Lcd_Cmd(0x0f); //iniciamos cursor
    while (1)// LOOP PRINCIPAL
    {

        temperatura1 = (temp_temp1 * (0.7058)) - 68; // conversiones para valores analógicos
        temperatura2 = (temp_temp2 * (0.7058)) - 68;
        luz1 = (temp_luz1 * (0.3921)) + 1;
        luz2 = (temp_luz2 * (0.3921)) + 1;

        if (bandera_info) {/// Se solicita la informacion del esclavo 1

            //Dirección para esclavo 1 es 0x50
            I2C_Master_Start();
            I2C_Master_Write(0x50);
            I2C_Master_Write(0b10000000); // Petición temperatura 1
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x51);
            temp_temp1 = I2C_Master_Read(0); //Se hace lectura de lo que se pidió
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x50);
            I2C_Master_Write(0b01000000); // Petición temperatura 2
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x51);
            temp_temp2 = I2C_Master_Read(0); //Se hace lectura de lo que se pidió
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x50);
            I2C_Master_Write(0b11000000); // Petición Luz 1
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x51);
            temp_luz1 = I2C_Master_Read(0); //Se hace lectura de lo que se pidió
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x50);
            I2C_Master_Write(0b00100000); //Petición Luz 2
            I2C_Master_Stop();
            __delay_ms(200);

            I2C_Master_Start();
            I2C_Master_Write(0x51);
            temp_luz2 = I2C_Master_Read(0); //Se hace lectura de lo que se pidió
            I2C_Master_Stop();
            __delay_ms(200);

            bandera_info = 0;

        }


        if (bandera_lcd1) {// Se cambia la informacion mostrada en la pantalla
            Lcd_Clear();
            bandera_lcd = bandera_lcd ^ 1;
            bandera_lcd1 = 0;
        }

        if (bandera_lcd) {// Se muestran los datos en la pantalla depende de la bandera

            Lcd_Set_Cursor(1, 1); //posición inicial
            Lcd_Write_String(" LUZ2 VRS");
            Lcd_Set_Cursor(2, 1); //posición inicial
            Lcd_Write_String(" ");
            Lcd_Write_Char(int_string(BTD_CENTENA(luz2)));
            Lcd_Write_Char(int_string(BTD_DECIMAL(luz2)));
            Lcd_Write_Char(int_string(BTD_UNIDAD(luz2)));
            Lcd_Write_String("% ");

            Lcd_Write_Char(bandera_ventilador);
            Lcd_Write_Char(bandera_resistencia);
            Lcd_Write_Char(bandera_servo);


        } else if (!bandera_lcd) {// Se muestran los datos en la pantalla depende de la bandera

            Lcd_Set_Cursor(1, 1); //posición inicial
            Lcd_Write_String(" T1   T2   L1");
            Lcd_Set_Cursor(2, 0); //posición inicial
            Lcd_Write_String(" ");
            Lcd_Write_Char(int_string(BTD_CENTENA(temperatura1)));
            Lcd_Write_Char(int_string(BTD_DECIMAL(temperatura1)));
            Lcd_Write_Char(int_string(BTD_UNIDAD(temperatura1)));
            Lcd_Write_String("C ");
            Lcd_Write_Char(int_string(BTD_CENTENA(temperatura2)));
            Lcd_Write_Char(int_string(BTD_DECIMAL(temperatura2)));
            Lcd_Write_Char(int_string(BTD_UNIDAD(temperatura2)));
            Lcd_Write_String("C ");
            Lcd_Write_Char(int_string(BTD_CENTENA(luz1)));
            Lcd_Write_Char(int_string(BTD_DECIMAL(luz1)));
            Lcd_Write_Char(int_string(BTD_UNIDAD(luz1)));
            Lcd_Write_String("%");
        }

        if (bandera_serial) {// Se mandan los datos vía USART
            // print("TEMP1 TEMP2 LUZ1 LUZ2");
            // print("\n\r");
            enviar_letra('(');
            enviar_letra(int_string(BTD_CENTENA(temperatura1)));
            enviar_letra(int_string(BTD_DECIMAL(temperatura1)));
            enviar_letra(int_string(BTD_UNIDAD(temperatura1)));
            enviar_letra(',');
            enviar_letra(int_string(BTD_CENTENA(temperatura2)));
            enviar_letra(int_string(BTD_DECIMAL(temperatura2)));
            enviar_letra(int_string(BTD_UNIDAD(temperatura2)));
            enviar_letra(',');
            enviar_letra(int_string(BTD_CENTENA(luz1)));
            enviar_letra(int_string(BTD_DECIMAL(luz1)));
            enviar_letra(int_string(BTD_UNIDAD(luz1)));
            enviar_letra(',');
            enviar_letra(int_string(BTD_CENTENA(luz2)));
            enviar_letra(int_string(BTD_DECIMAL(luz2)));
            enviar_letra(int_string(BTD_UNIDAD(luz2)));
            enviar_letra(')');
            print("\n\r");


            bandera_serial = 0;
        }

        if ((temperatura1 < temp_nom || temperatura2 < temp_nom)) { // Se evualuan datos y depende de la temperatura se mandan datos del esclavo 2




            I2C_Master_Start(); // Se envía para que enciendan los sistemas
            I2C_Master_Write(0x60);
            I2C_Master_Write(0x01);
            I2C_Master_Stop();
            __delay_ms(200);

            bandera_ventilador = '1';
            bandera_resistencia = '1';
            bandera_servo = '1';


        } else if ((temperatura1 > temp_nom && temperatura2 > temp_nom)) {


            I2C_Master_Start(); // Se mandan la señal para desactivar sistemas
            I2C_Master_Write(0x60);
            I2C_Master_Write(0x02);
            I2C_Master_Stop();

            bandera_ventilador = '0';
            bandera_resistencia = '0';
            bandera_servo = '0';
        }

    }
}

void setup(void) {



    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1; // 8MHz
    OSCCONbits.IRCF0 = 1;

    //CONFIGURACION IO
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0X00;
    TRISD = 0X00;
    TRISE0 = 0;
    TRISE1 = 0;
    TRISE2 = 0X00;
    PORTB = 0X00;
    PORTD = 0X00;
    RE0 = 0;


    // INTERRUPCIONES
    INTCONbits.GIE = 1; // HABILITAR INTERRUPCIONES GLOBALES
    INTCONbits.PEIE = 1; // HABILITAR INTERRUPCIONES PERIFERICOS

    // CONFIGURAR EUSART TRANSMITER Y RECEPTOR

    SPBRGH = 0; //BYTE SUPERIOR 9600 BAUD RATE con 8 MHz
    SPBRG = 12; //BYTE INFERIOR
    BRGH = 0;
    BRG16 = 0;

    TXSTAbits.SYNC = 0; // LO PONEMOS COMO ASINCRONO
    RCSTAbits.SPEN = 1; // HABILITA EL EUSART Y CONFIGURA LOS TINES TX/CK I/O COMO SALIDA
    TXSTAbits.TXEN = 1; // ACTIVA EL CIRCUITO PARA TRASMISOR DEL EUSART
    RCSTAbits.CREN = 1; // ACTIVA EL CIRCUITO PARA EL RECEPTOR DE EUSART
    //PIE1bits.TXIE = 1; //ES PARA INTERRUPCIONES TRANSMISOR
    PIE1bits.RCIE = 1; //ES PARA INTERRUPCIONES RECEPTOR  

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


    I2C_Master_Init(100000); // Inicializar Comuncación I2C




}




















