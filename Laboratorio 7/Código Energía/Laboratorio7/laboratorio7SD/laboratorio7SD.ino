#include <SPI.h>//librerias
#include <SD.h>
#include <stdio.h>
#include <stdlib.h>


String archivos[6];// variables 

File root;
File myFile;

unsigned char menu;
unsigned char entrada;
unsigned char imprimir;
unsigned char habilitado;


void setup() {
  SPI.setModule(0);//iniciar modulo spi y uart
  Serial.begin(115200);

  pinMode(PA_3, OUTPUT);// CS in SD card

  if (!SD.begin(PA_3)) {
    //Serial.println("initialization failed!");
    return;
  }
  //Serial.println("initialization done.");
  root = SD.open("/");
  printDirectory(root, 0);

  // valores iniciales
  menu = 0;
  entrada = 0;
  imprimir = 1;

}

void loop() {
  if (Serial.available()) {
    entrada = Serial.read();
  }

  if (menu == 0) {
    if (imprimir == 1) {
      espacio(10);
      Serial.println("Introduzca el numero de la opcion que desea");
      Serial.println("1) Ver archivos disponibles en SD");
      Serial.println("2) Desplegar imagenes");
      imprimir = 0;
    }
    if (entrada == '1') {
      menu = 1 ;
      imprimir = 1;
    } else if (entrada == '2') {
      menu = 2 ;
      imprimir = 1;
    }
    /////////////////////////////////////////////////////////////
  } else if (menu == 1) {
    if (imprimir == 1) {

      espacio(10);
      Serial.println("Los archivos disponibles son:");
      Serial.println("");
      for (int i = 1; i < 7; i++) {
        Serial.print(i);
        Serial.print(") ");
        Serial.println(archivos[i]);
      }
      Serial.println("a) Atras");
      imprimir = 0;

    }


    if (entrada == 'a') {
      menu = 0 ;
      imprimir = 1;
    }


    //////////////////////////////////////////////////////////////
  } else if (menu == 2) {
    if (imprimir == 1) {
      espacio(10);
      Serial.println("Ingrese el numero de la figura que desea imprimir");
      Serial.println("a) Atras");
      imprimir = 0;
      entrada = 0;
    }
    if (string_int(entrada) > 0 && string_int(entrada) < 7) {
      habilitado = 1;
    }

    if (entrada != 'a') {

      if (habilitado == 1) {
        if (entrada == '1') {
          myFile = SD.open("figura1.TXT");
        } else if (entrada == '2') {
          myFile = SD.open("figura2.TXT");
        }
        else if (entrada == '3') {
          myFile = SD.open("figura3.TXT");
        }
        if (myFile) {
          //Serial.println("figura"+string_int(entrada));

          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
          imprimir = 1;
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening test.txt");
          imprimir = 1;
        }

        habilitado = 0;
        entrada = 0;
        imprimir = 1;
      }


    } else if (entrada == 'a') {
      menu = 0 ;
      imprimir = 1;
    }
  }

}


void printDirectory(File dir, int numTabs) {//hacer lista de archivos disponibles
  int i = 0;


  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {
      // no hay mas archivos
      break;
    }

    if (entry.size() > 9000 && entry.size() < 30000) {
      i++;

      archivos[i] = entry.name();

    }


    entry.close();
  }

}

void espacio(unsigned char tamano) {
  for (int i = 0; i < tamano; i++) {
    Serial.println("");
  }
}

unsigned char string_int(unsigned char numero) {
  switch (numero) {
    case ('1'):  return (1); break;
    case ('2'):  return (2); break;
    case ('3'):  return (3); break;
    case ('4'):  return (4); break;
    case ('5'):  return (5); break;
    case ('6'):  return (6); break;
  }
}
