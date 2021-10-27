/*Proyecto Video Juego
   Video Juego: Flappy Bird 1 tivas, 3 esp32
   Autores: Axel Mazariegos y Estephan Portales
   Iniciado: 10/10/21
   Terminado:
   Modificaciones:
   Universidad Del Valle de Guatemala
*/

#include <SPI.h>//librerias
#include <SD.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"


#define NOTE_B0  31// notas para música
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

#define LCD_RST PD_0 ///pines para display
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
#define boton1 PF_0
#define boton2 PF_4
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
/////////////////////////////////////////////////////////////////////////////////////////////             VARIABLES

unsigned char estado;// para saber en que pantalla estamos la 0 es el inicio
unsigned char bandera_pantalla;
unsigned char bandera_pilar;
unsigned char bandera_pilar1;
unsigned char posicion_menu;
int entrada_serial;
int altura_pajaro = 100;// jugador principal
int altura_pajaro2 = 100; // jugador 2
unsigned char bandera_perder;//JUGADOR1
unsigned char bandera_perder2;//JUGADOR2

unsigned char visi1 = 1;
unsigned char visi2 = 0;
unsigned char visibilidad = visi1;
unsigned char visibilidad2 = visi2;
int punteo;
int punteo2;
int punteo_gen1;
int punteo_gen2;
int validar_punto = 0;
int validar_punto2 = 0;

////Recepcion de datos
//String posiciony;
//String alturabloques;
//String alturabloquei;
//String posicionx;

int caida;
int caida2;

int alturaP1;
int anchoP = 30;
int alturaP2;

const int retraso = 1;//pilar 1
unsigned long transcurrido;

const int retraso1 = 1;// pilar 2
unsigned long transcurrido1;

int tiempo_vivo1;
int tiempo_vivo2;
unsigned long tiempo_v1;


//creamos pilares

int pilars_ancho = 25;//pilar 1
int pilars_altura = 0;//random(0, 219);
int pilars_posx = 230;

int pilars_ancho1 = 25;//pilar 2
int pilars_altura1 = 0;//random(0, 219);
int pilars_posx1 = 230;

int pilari_ancho = 15;//pilar1
int pilari_altura = 0;//239 - pilars.altura - 20;

int pilari_ancho1 = 15;//pilar 2
int pilari_altura1 = 0;//239 - pilars.altura - 20;
//pilari_posx = 230;

int tempo = 300;// duracion de la cancion


#define buzzer PF_2// pin de la bocina

//melodía a reproducir

int melody[] = {


  REST, 2, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8, //1
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 8, NOTE_A4, 8, NOTE_FS5, 8, NOTE_E5, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 4, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,

  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_G4, 4, NOTE_B4, 8, //7
  NOTE_A4, 4, NOTE_B4, 8, NOTE_A4, 4, NOTE_D4, 2,
  REST, 4, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 8, NOTE_A4, 8, NOTE_FS5, 8, NOTE_E5, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,

  REST, 4, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8, //13
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_G4, 4, NOTE_B4, 8,
  NOTE_A4, 4, NOTE_B4, 8, NOTE_A4, 4, NOTE_D4, 8, NOTE_D4, 8, NOTE_FS4, 8,
  NOTE_E4, -1,
  REST, 8, NOTE_D4, 8, NOTE_E4, 8, NOTE_FS4, -1,

  REST, 8, NOTE_D4, 8, NOTE_D4, 8, NOTE_FS4, 8, NOTE_F4, -1, //20
  REST, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_E4, -1, //end 1

  //repeats from 1

  REST, 2, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8, //1
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 8, NOTE_A4, 8, NOTE_FS5, 8, NOTE_E5, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 4, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,

  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_G4, 4, NOTE_B4, 8, //7
  NOTE_A4, 4, NOTE_B4, 8, NOTE_A4, 4, NOTE_D4, 2,
  REST, 4, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 8, NOTE_A4, 8, NOTE_FS5, 8, NOTE_E5, 4, NOTE_D5, 8,
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,

  REST, 4, NOTE_D5, 8, NOTE_B4, 4, NOTE_D5, 8, //13
  NOTE_CS5, 4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_A4, 2,
  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_G4, 4, NOTE_B4, 8,
  NOTE_A4, 4, NOTE_B4, 8, NOTE_A4, 4, NOTE_D4, 8, NOTE_D4, 8, NOTE_FS4, 8,
  NOTE_E4, -1,
  REST, 8, NOTE_D4, 8, NOTE_E4, 8, NOTE_FS4, -1,

  REST, 8, NOTE_D4, 8, NOTE_D4, 8, NOTE_FS4, 8, NOTE_F4, -1, //20
  REST, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_E4, 8, //end 2
  NOTE_E4, -2, NOTE_A4, 8, NOTE_CS5, 8,
  NOTE_FS5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_A5, -4,

};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;

int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

int delay_musica;
unsigned long millis_musica;
int thisNote;

unsigned char music_enable = 1;

unsigned char bandera_recibir = 1;

unsigned char configuraciones = 1;

File myFile;


//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);
void LCD_Bitmap_mod(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap);
unsigned char string_int(unsigned char numero); void mostrar_imasd( char height1, char width1, char height2, char width2);
void botones(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
void pilares(int x, int y);


//***************************************************************************************************************************************
// Initialization
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);// inicializaciones
  SPI.setModule(0);
  Serial.begin(115200);//Baud Rate
  Serial2.begin(115200);//RS232: Rx = PD6; Tx = PD7
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);//para pantalla
  pinMode(PA_3, OUTPUT);// CS in SD card
  //Serial.println("Start");
  LCD_Init();
  LCD_Clear(0x00);


  if (!SD.begin(PA_3)) {// iniciar SD
    // Serial.println("initialization failed!");
    return;
  }
  // Serial.println("initialization done.");

  //myFile = SD.open("HOME.TXT", FILE_READ);
  //mostrar_imasd(0, 25, 320, 240);


  // delay(2000);

  //// valores iniciales
  estado = 0; //empezamos en la pantalla de menu
  bandera_pantalla = 1;
  posicion_menu = 1;
  bandera_pilar = 1;
  bandera_perder = 0;
  caida = 2;
  caida2 = 2;
  punteo = 0;
  punteo2 = 0;

  visibilidad = 1;
  visibilidad2 = 0;




  randomSeed(random(100));




}
//***************************************************************************************************************************************
// Loop
//***************************************************************************************************************************************
void loop() {

  if (bandera_recibir == 1) {
    if (Serial2.available() > 0) {
      entrada_serial = Serial2.read();
    }
  }

  if (estado == 0 ) {//menu
    if (bandera_pantalla == 1) {
      Serial2.flush();
      myFile = SD.open("MENU.TXT", FILE_READ);
      mostrar_imasd(0, 0, 319, 239);//mostrar_imasd(0, 0, 319, 240);

      bandera_pantalla = 0;

      bandera_recibir = 1;
      Serial2.flush();  entrada_serial = 0;
    }
    //posicion_menu

    if (entrada_serial == 'U') {
      posicion_menu--;
      if (posicion_menu < 1) {
        posicion_menu = 3;
      }
      Serial2.flush();  entrada_serial = 0;

    } else if (entrada_serial == 'D') {
      posicion_menu++;
      if (posicion_menu > 3) {
        posicion_menu = 1;
      }
      Serial2.flush();  entrada_serial = 0;
    }


    if (posicion_menu == 1) {// para que cambie de pantalla
      // hacemos indicadores
      //0xD71E color pantalla original  el otro es 0x8040
      botones(1, 0, 0, 0);

      //si seleciona
      if (entrada_serial == 'P') {
        estado = 1;
        bandera_pantalla = 1;
        posicion_menu = 1;
        Serial2.flush();  entrada_serial = 0;
        caida = 2 ;
        caida2 = 2;
      }

    } else if (posicion_menu == 2) {// para que cambie de pantalla
      // hacemos indicadores
      //0xD71E color pantalla original  el otro es 0x8040
      botones(0, 1, 0, 0);
      //si seleciona
      if (entrada_serial == 'P') {
        estado = 2;
        bandera_pantalla = 1;
        posicion_menu = 1;
        Serial2.flush();  entrada_serial = 0;

      }
    }
    else if (posicion_menu == 3) {
      // hacemos indicadores
      //0xD71E color pantalla original  el otro es 0x8040
      botones(0, 0, 1, 0);
      //si seleciona
      if (entrada_serial == 'P') {// para que cambie de pantalla
        estado = 3;
        bandera_pantalla = 1;
        posicion_menu = 1;
        Serial2.flush();  entrada_serial = 0;

      }



    }
  } else if (estado == 1) { //ENTRAR AL JUEGO
    if (bandera_pantalla == 1) {
      Serial2.flush();
      myFile = SD.open("BACK.TXT", FILE_READ);
      mostrar_imasd(0, 0, 319, 240);
      altura_pajaro = 100;
      altura_pajaro2 = 100;
      bandera_pantalla = 0;
      //////////////////////////////////////////////Verificar que los dos jugadores estan listos
      // LCD_Print("Emparejando...", 60, 30, 2, 0x0000, 0xA61E);// NO SE USA PORQUE NO HAY OTRA TIVA :(


      // while (Serial2.read() != 'N') {
      //  Serial2.write('N');
      // }
      // LCD_Print("Emparejando...", 60, 30, 2, 0xA61E, 0xA61E);
    }





    ////////////////////////////////RECIBIR DATOS DEL OTRO JUGADOR(receiver), se debe ajutar para que el master solo reciba posicion 'y' del pajaro y si el otro jugador perdio

    /*String posiciony;
      String alturabloques;
      String alturabloquei;  strings a usar para cada cosa
      String posicionx;*/

    /*if (entrada_serial == 'Y') {
      String posiciony = Serial2.readStringUntil('L');//B para receiver y L para master //// NO SE USA PORQUE NO HAY OTRA TIVA
      Serial2.flush();  entrada_serial = 0;
      altura_pajaro2 = posiciony.toInt();
      //Serial.println(altura_pajaro2);
      } //*else if (entrada_serial == 'B') {
      String alturabloques = Serial2.readStringUntil('V');
      pilars_altura = alturabloques.toInt();
      } else if (entrada_serial == 'V') {
      String alturabloquei = Serial2.readStringUntil('X');
      pilari_altura = alturabloquei.toInt();
      }else if (entrada_serial == 'X'){
      String posicionx = Serial2.readStringUntil('L');
      pilars_posx = posicionx.toInt();
      }*/

    ///////////////////////////////////////////////////////////////// juego juego
    /// controles para saltar
    if (entrada_serial == 'P') {
      caida = -3;
      Serial2.flush();  entrada_serial = 0;
    } else if (entrada_serial == 'I') {
      caida = 2;
      Serial2.flush();  entrada_serial = 0;
    } /*else if (entrada_serial == 'F') { //////////////////////////////////// Perdio el amigo, hacer otra ventana de ganador
      estado = 5;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      bandera_pantalla = 1;
    }*/
    else if (entrada_serial == 'N') {
      caida2 = -3;
      Serial2.flush();  entrada_serial = 0;
    } else if (entrada_serial == 'M') {
      caida2 = 2;
      Serial2.flush();  entrada_serial = 0;
    }


    ////////////////////////////////////////////////////////////////////////////////////////// MUSICA
    if (music_enable == 1) {
      if (millis() >= delay_musica + millis_musica) {
        millis_musica = millis();
        thisNote = thisNote + 2;
        if (thisNote < notes * 2) {
          // calculates the duration of each note
          divider = melody[thisNote + 1];
          if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
          }

          tone(buzzer, melody[thisNote], noteDuration * 0.9);

          delay_musica = noteDuration;

        }
      }
    }

    if (thisNote > notes * 2) {
      thisNote = 0;
      delay_musica = 0;
      //notes = sizeof(melody) / sizeof(melody[0]) / 2;
      //wholenote = (60000 * 4) / tempo;
      divider = 0, noteDuration = 0;
    }



    /////////////////////////////////////////////////////////////////////////////tiempo vivos


    if (millis() >= 1000 + tiempo_v1) {
      tiempo_v1 = millis();
      if (visibilidad == 1) {
        tiempo_vivo1++;
      } if (visibilidad2 == 1) {
        tiempo_vivo2++;
      }
    }

    /////////////////////////////////////////////////////////////////////////////

    if ((bandera_perder == 1 && bandera_perder2 == 1) and (visi1 == 1 && visi2 == 1)) {

      bandera_pantalla = 1;
      bandera_perder = 0;
      bandera_perder2 = 0;
      estado = 4;
      bandera_recibir = 0;
    }
    else if ((bandera_perder == 1) and (visi1 == 1 && visi2 == 0)) {

      bandera_pantalla = 1;
      bandera_perder = 0;
      bandera_perder2 = 0;
      estado = 4;
      bandera_recibir = 0;
    }





    //////////////////////////////////////////////////////////////////////////////////////////////////////PUNTEO JUGADOR





    /////////////////////////////////////////////////// pajaro segundario se controla segun lo que se reciba

    ///////////////////////////////////////// esta parte se deshabilita para el receiver///////////////////////////////////
    if (bandera_pilar == 1) {
      pilars_ancho = 25;
      pilars_altura = random(127); //158
      pilars_posx = 319;
      pilari_altura = 140 - pilars_altura ;//158 140
      //int pos1 = 230;
      bandera_pilar = 0;

    }


    //FillRect(x,y,w,h,c);
    ///////////////////////////////////////////////////////////////// se quita el millis() para el receiver y la parte de arriba con la bandera_pilar
    if (millis() > retraso + transcurrido) {
      transcurrido = millis();
      FillRect(pilars_posx, 15, pilars_ancho, pilars_altura, 0X7200);  //pilar 1
      FillRect(pilars_posx, 218 - pilari_altura, pilars_ancho, pilari_altura, 0X7200);
      pilars_posx = pilars_posx - 3; //// se deshabilita para receiver
      V_line(pilars_posx + 26, 15, pilars_altura, 0xA61E);
      V_line(pilars_posx + 28, 15, pilars_altura, 0xA61E);
      V_line(pilars_posx + 27, 15, pilars_altura, 0xA61E);
      V_line(pilars_posx + 26, 218 - pilari_altura, pilari_altura, 0xA61E);
      V_line(pilars_posx + 28, 218 - pilari_altura, pilari_altura, 0xA61E);
      V_line(pilars_posx + 27, 218 - pilari_altura, pilari_altura, 0xA61E);




      if (pilars_posx <= -25) {
        bandera_pilar = 1;
      }


    }


    //////////////////////////////////////////////////////////////////////////////////Saber si choco con pilar o  si tuvo punto/////////////////////////////////////////////////////////////////

    if (visibilidad == 1) {

      String text2 = String (punteo);
      LCD_Print(text2, 200, 30, 2, 0x0000, 0xA61E);



      altura_pajaro = altura_pajaro + caida;
      int index = (altura_pajaro / 11) % 8;

      //LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
      LCD_Sprite(100, altura_pajaro , 35, 28, jugador1, 2, index, 0, 102);
      H_line( 100, altura_pajaro + 29, 35, 0xA61E);
      H_line( 100, altura_pajaro - 1, 35, 0xA61E);



      if (pilars_posx > 65 && pilars_posx < 135) {//65 135
        validar_punto = 1; /// para que por cada pilar solo suba 1 punto
        if (((altura_pajaro - 11) < pilars_altura) or ((altura_pajaro + 26) >  (218 - pilari_altura)) ) { //quitar bordes extra, // es para saber si choca con pilares//30
          bandera_perder = 1;
          visibilidad = 0;
          FillRect(100, altura_pajaro, 35, 28, 0xA61E);//limpiamos pajaro
        }
      }
      else if ((pilars_posx < 65) and ( bandera_perder == 0) and ( validar_punto == 1)) {
        punteo++;
        validar_punto = 0;
      }


      if (altura_pajaro < 16) {
        bandera_perder = 1;
        visibilidad = 0;
        FillRect(100, altura_pajaro, 35, 28, 0xA61E);//limpiamos pajaro

      } else if (altura_pajaro > 186) {
        bandera_perder = 1;
        visibilidad = 0;
        FillRect(100, altura_pajaro, 35, 28, 0xA61E);//limpiamos pajaro

      }

    }
    //////////////////////////////////////////////////////
    if (visibilidad2 == 1) {
      String text1 = String(punteo2);
      LCD_Print(text1, 80, 30, 2, 0x0000, 0xA61E);

      altura_pajaro2 = altura_pajaro2 + caida2;
      int  index1 = (altura_pajaro2 / 11) % 8;//////////////////////////////////////////////////// queda pendiente de revisar con salva
      //LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
      LCD_Sprite(55, altura_pajaro2 , 35, 28, jugador2, 2, index1, 0, 102);
      H_line( 55, altura_pajaro2 + 29, 35, 0xA61E);
      H_line( 55, altura_pajaro2 - 1, 35, 0xA61E);
      // }

      if (pilars_posx > 20 && pilars_posx < 90) {
        validar_punto2 = 1; /// para que por cada pilar solo suba 1 punto
        if (((altura_pajaro2 - 11) < pilars_altura) or ((altura_pajaro2 + 26) >  (218 - pilari_altura)) ) {
          bandera_perder2 = 1;
          visibilidad2 = 0;
          FillRect(55, altura_pajaro2, 35, 28, 0xA61E);//limpiamos pajaro

        }

      }
      else if ((pilars_posx < 20 and bandera_perder2 == 0) and validar_punto2 == 1) {
        punteo2++;

        validar_punto2 = 0;
      }



      if (altura_pajaro2 < 16) {
        bandera_perder2 = 1;
        visibilidad2 = 0;
        FillRect(55, altura_pajaro2, 35, 28, 0xA61E);//limpiamos pajaro

      } else if (altura_pajaro2 > 186) {
        bandera_perder2 = 1;
        visibilidad2 = 0;
        FillRect(55, altura_pajaro2, 35, 28, 0xA61E);//limpiamos pajaro

      }
    }







    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* Serial2.print('Y');///////////////////////// NO ESTA EN USO PORQUE NO HAY TIVA 2
      Serial2.print(altura_pajaro);
      Serial2.print('B');
      Serial2.print(pilars_altura);
      Serial2.print('V');
      Serial2.print(pilari_altura);
      Serial2.print('X');
      Serial2.print(pilars_posx);
      Serial2.print('L');*/





    ////////////////////////////////////////////////////////////////////////////////////////////////

  } else if (estado == 2) { // registro
    if (bandera_pantalla == 1) {
      Serial2.flush();
      configuraciones = 1;
      FillRect(0, 0, 319, 239, 0xffff);
      LCD_Print("CONFIGURACIONES", 35, 20, 2, 0x0000, 0Xffff);
      LCD_Print("AUDIO: ", 5, 50, 2, 0x0000, 0Xffff);
      LCD_Print("JUGADORES: ", 5, 80, 2, 0x0000, 0Xffff);

      bandera_pantalla = 0;
    }

    if (configuraciones == 1) { /// audio

      if (entrada_serial == 'D') {
        LCD_Print("ON ", 100, 50, 2, 0x0000, 0Xffff);
        music_enable = 1;
        Serial2.flush();  entrada_serial = 0;
      } else if (entrada_serial == 'U') {
        LCD_Print("OFF", 100, 50, 2, 0x0000, 0Xffff);
        music_enable = 0;
        Serial2.flush();  entrada_serial = 0;
      } else if (entrada_serial == 'P') {
        configuraciones = 2;
        Serial2.flush();  entrada_serial = 0;
      }


    } else if (configuraciones == 2) { // jugadores

      if (entrada_serial == 'D') {
        LCD_Print("1", 160, 80, 2, 0x0000, 0Xffff);
        visi1 = 1;
        visi2 = 0;
        visibilidad = visi1;
        visibilidad2 = visi2;
        Serial2.flush();  entrada_serial = 0;
      } else if (entrada_serial == 'U') {
        LCD_Print("2", 160, 80, 2, 0x0000, 0Xffff);
        visi1 = 1;
        visi2 = 1;
        visibilidad = visi1;
        visibilidad2 = visi2;
        Serial2.flush();  entrada_serial = 0;
      } else if (entrada_serial == 'P') {
        estado = 0;
        bandera_pantalla = 1;
        Serial2.flush();  entrada_serial = 0;
      }
    }




    /* estado = 0;
      bandera_pantalla = 1;*/


  } else if (estado == 3) { //INFORMACION
    if (bandera_pantalla == 1) {
      Serial2.flush();
      myFile = SD.open("INFO.TXT", FILE_READ);
      mostrar_imasd(0, 0, 319, 240);

      bandera_pantalla = 0;
    }
    ///// hacer indicador de seleccion
    botones(0, 0, 0, 1);

    if (entrada_serial == 'P') {// para que cambie de pantalla
      estado = 0;
      bandera_pantalla = 1;
      Serial2.flush();  entrada_serial = 0;

    }
  } else if (estado == 4) { // GAME OVER
    bandera_perder = 1;
    if (bandera_pantalla == 1) {
      Serial2.flush();  entrada_serial = 0;
      //myFile = SD.open("OVER.TXT", FILE_READ);
      // mostrar_imasd(0, 0, 319, 239);//////////////////// mostrar resultados
      FillRect(0, 0, 319, 239, 0xffff);



      if (visi1 == 1 && visi2 == 1) {
        LCD_Print("RESULTADOS", 80, 20, 2, 0x0000, 0Xffff);
        LCD_Print("JUGADOR 1 ", 5, 50, 2, 0x0000, 0Xffff);
        LCD_Print("JUGADOR 2 ", 175, 50, 2, 0x0000, 0Xffff);
        String text1 = String(punteo);
        LCD_Print("PUNTEO: ", 5, 100, 2, 0x0000, 0Xffff);
        LCD_Print(text1, 120, 100, 2, 0x0000, 0Xffff);
        String text2 = String(punteo2);
        LCD_Print("PUNTEO: ", 175, 100, 2, 0x0000, 0Xffff);
        LCD_Print(text2, 285, 100, 2, 0x0000, 0Xffff);

        String text3 = String(tiempo_vivo1);
        LCD_Print("Tiempo Vivo (Seg) ", 0, 150, 2, 0x0000, 0Xffff);
        LCD_Print("J1: ", 5, 180, 2, 0x0000, 0Xffff);
        LCD_Print(text3, 55, 180, 2, 0x0000, 0Xffff);

        String text4 = String(tiempo_vivo2);
        LCD_Print("J2: ", 5, 200, 2, 0x0000, 0Xffff);
        LCD_Print(text4, 55, 200, 2, 0x0000, 0Xffff);
      }
      else if (visi1 == 1 && visi2 != 1) {
        LCD_Print("RESULTADOS", 80, 20, 2, 0x0000, 0Xffff);
        LCD_Print("JUGADOR 1 ", 5, 50, 2, 0x0000, 0Xffff);
        String text1 = String(punteo);
        LCD_Print("PUNTEO: ", 5, 100, 2, 0x0000, 0Xffff);
        LCD_Print(text1, 120, 100, 2, 0x0000, 0Xffff);

        String text3 = String(tiempo_vivo1);
        LCD_Print("Tiempo Vivo (Seg) ", 0, 150, 2, 0x0000, 0Xffff);
        LCD_Print("J1: ", 5, 180, 2, 0x0000, 0Xffff);
        LCD_Print(text3, 55, 180, 2, 0x0000, 0Xffff);

      }
      bandera_pantalla = 0;
      bandera_recibir = 1;
      Serial2.flush(); entrada_serial = 0;
      delay(1500);
      Serial2.flush();  entrada_serial = 0;
    }
    if (entrada_serial == 'P') {// para que cambie de pantalla
      estado = 0;//al menu
      bandera_pantalla = 1;
      altura_pajaro = 100;
      altura_pajaro2 = 100;
      bandera_perder = 0;
      bandera_perder2 = 0;

      bandera_pilar = 1;
      visibilidad = visi1;
      visibilidad2 = visi2;
      tiempo_vivo2 = 0;
      tiempo_vivo1 = 0;
      punteo = 0;
      punteo2 = 0;
      randomSeed(random(100));


      thisNote = 0;/// musica se reinicia
      delay_musica = 0;
      // notes = sizeof(melody) / sizeof(melody[0]) / 2;
      // wholenote = (60000 * 4) / tempo;
      divider = 0, noteDuration = 0;
      bandera_recibir = 0;
      Serial2.flush();  entrada_serial = 0;
    }
  }
  else if (estado == 5) { // GANAR
    bandera_perder = 1;
    if (bandera_pantalla == 1) {
      Serial2.flush();
      myFile = SD.open("GANAR.TXT", FILE_READ);
      mostrar_imasd(0, 0, 319, 239);
      bandera_pantalla = 0;
    }
    if (entrada_serial == 'P') {// para que cambie de pantalla
      Serial2.flush();
      estado = 0;//al menu
      bandera_pantalla = 1;
      altura_pajaro = 100;
      Serial2.flush();  entrada_serial = 0;

    }
  }
}

//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void botones(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4) {
  if (b1 == 1) {
    //0xD71E color pantalla original  el otro es 0x8040
    FillRect(120, 66, 78, 5, 0x8040 );//primer boton
    FillRect(120, 66, 5, 32, 0x8040 );
    FillRect(120, 97, 78, 5, 0x8040);
    FillRect(197, 66, 5, 36, 0x8040 );

    FillRect(120, 102, 78, 5, 0xD71E);//segundo boton
    FillRect(120, 102, 5, 32, 0xD71E);
    FillRect(120, 129, 78, 5, 0xD71E);
    FillRect(197, 102, 5, 32, 0xD71E);

    FillRect(120, 137, 78, 5, 0xD71E);//tercer boton
    FillRect(120, 137, 5, 32, 0xD71E);
    FillRect(120, 163, 78, 5, 0xD71E);
    FillRect(197, 137, 5, 32, 0xD71E);



  } if (b2 == 1) {
    //0xD71E color pantalla original  el otro es 0x8040
    FillRect(120, 66, 78, 5, 0xD71E );//primer boton
    FillRect(120, 66, 5, 32, 0xD71E );
    FillRect(120, 97, 78, 5, 0xD71E);
    FillRect(197, 66, 5, 36, 0xD71E );

    FillRect(120, 102, 78, 5, 0x8040);//segundo boton
    FillRect(120, 102, 5, 32, 0x8040);
    FillRect(120, 129, 78, 5, 0x8040);
    FillRect(197, 102, 5, 32, 0x8040);

    FillRect(120, 137, 78, 5, 0xD71E);//tercer boton
    FillRect(120, 137, 5, 32, 0xD71E);
    FillRect(120, 163, 78, 5, 0xD71E);
    FillRect(197, 137, 5, 32, 0xD71E);



  } if (b3 == 1) {
    //0xD71E color pantalla original  el otro es 0x8040
    FillRect(120, 66, 78, 5, 0xD71E );//primer boton
    FillRect(120, 66, 5, 32, 0xD71E );
    FillRect(120, 97, 78, 5, 0xD71E);
    FillRect(197, 66, 5, 36, 0xD71E );

    FillRect(120, 102, 78, 5, 0xD71E);//segundo boton
    FillRect(120, 102, 5, 32, 0xD71E);
    FillRect(120, 129, 78, 5, 0xD71E);
    FillRect(197, 102, 5, 32, 0xD71E);

    FillRect(120, 137, 78, 5, 0x8040);//tercer boton
    FillRect(120, 137, 5, 31, 0x8040);
    FillRect(120, 163, 78, 5, 0x8040);
    FillRect(197, 137, 5, 31, 0x8040);



  } if (b4 == 1) {
    //0xD71E color pantalla original  el otro es 0x8040


    FillRect(3, 175, 78, 5, 0x8040);//tercer boton
    FillRect(3, 175, 5, 31, 0x8040);
    FillRect(3, 205, 78, 5, 0x8040);
    FillRect(78, 175, 5, 35, 0x8040);
  }

}

void pilares(int x, int y) {
  if (x >= 270) {
    FillRect(318, 0, x, y - 1, 0xee00);
    FillRect(319, 0, x - 1, y, 0xee00);
    FillRect(318, y + 81, x, 203, 0xee00);
    Rect(319, y + 80, x - 1, 204, 0x00);
  } else if (x <= 268) {
    FillRect(x + 51, 0, x + 60, y, 0xee00);
    FillRect(x + 49, 1, x + 1, y - 1, 0xee00);
    Rect(x + 50, 0, x, y, 0x00);
    FillRect(x - 1, 0, x - 3, y, 0xee00);

    FillRect(x + 51, y + 80, x + 60, 204, 0xee00);
    FillRect(x + 49, y + 81, x + 1, 203, 0xee00);
    Rect(x + 50, y + 80, x, 204, 0x00);
    FillRect(x - 1, y + 80, x - 3, 204, 0xee00);

  }
}

void mostrar_imasd( int width1, int height1, int width2, int height2) {
  int arreglotemporal[4];// Para interpretar los datos
  int arreglo3[3];
  int arreglo2[2];
  int arreglo1[1];
  int valor;
  int temporal = 0;
  char contador = 0;


  if (myFile) {// Leer datos de SD y mostrar en pantalla
    LCD_Clear(0x00);
    LCD_CMD(0x02c); // write_memory_start

    digitalWrite(LCD_RS, HIGH);
    digitalWrite(LCD_CS, LOW);

    SetWindows(width1, height1, width2 , height2 ); // poner pantalla
    while (myFile.available()) {

      temporal = myFile.read();

      if (temporal != ',' and temporal != ' ' and temporal != '\n' and temporal != '\r' ) {// evitar caracteres que no queremos
        arreglotemporal[contador] = temporal ;
        contador++;
      }
      else if (temporal == ',') {

        if (contador == 3) {
          arreglo3[0] = string_int(arreglotemporal[0]);// Para interpretar los datos
          arreglo3[1] = string_int(arreglotemporal[1]);
          arreglo3[2] = string_int(arreglotemporal[2]);
          valor = arreglo3[0] * 100;
          valor = valor + arreglo3[1] * 10;
          valor = valor + arreglo3[2];
          contador = 0;

        } else if (contador == 1) {
          arreglo1[0] = string_int(arreglotemporal[0]);
          valor = arreglo1[0];
          contador = 0;

        } else if (contador == 2) {
          arreglo2[0] = string_int(arreglotemporal[0]);
          arreglo2[1] = string_int(arreglotemporal[1]);
          valor = arreglo2[0] * 10;
          valor = valor + arreglo2[1];
          contador = 0;
        }
        LCD_DATA(valor);
        contador = 0;

      }

    }
    digitalWrite(LCD_CS, HIGH);// Poner pantalla a modo en el que estaba
    myFile.close();
    contador = 0;

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");

  }

}
unsigned char string_int(unsigned char numero) {
  switch (numero) {
    case ('0'):  return (0); break;
    case ('1'):  return (1); break;
    case ('2'):  return (2); break;
    case ('3'):  return (3); break;
    case ('4'):  return (4); break;
    case ('5'):  return (5); break;
    case ('6'):  return (6); break;
    case ('7'):  return (7); break;
    case ('8'):  return (8); break;
    case ('9'):  return (9); break;
  }
}

void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER)
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40 | 0x80 | 0x20 | 0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
  //  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c) {
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
    }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y + h, w, c);
  V_line(x  , y  , h, c);
  V_line(x + w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + w;
  y2 = y + h;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = w * h * 2 - 1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
      k = k - 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background)
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;

  if (fontSize == 1) {
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if (fontSize == 2) {
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }

  char charInput ;
  int cLength = text.length();
  // Serial.println(cLength, DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength + 1];
  text.toCharArray(char_array, cLength + 1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    // Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1) {
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2) {
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + width;
  y2 = y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k + 1]);
      //LCD_DATA(bitmap[k]);
      k = k + 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
void LCD_Bitmap_mod(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + width;
  y2 = y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap);
      //LCD_DATA(bitmap[k + 1]);
      //LCD_DATA(bitmap[k]);
      //k = k + 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 =   x + width;
  y2 =    y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  int k = 0;
  int ancho = ((width * columns));
  if (flip) {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width - 1 - offset) * 2;
      k = k + width * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k - 2;
      }
    }
  }
  else {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width + 1 + offset) * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k + 2;
      }
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
