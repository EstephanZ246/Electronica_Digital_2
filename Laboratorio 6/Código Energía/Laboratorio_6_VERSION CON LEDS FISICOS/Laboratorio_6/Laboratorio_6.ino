//Botones y led que se usaron
#define jugador1  31
#define jugador2  17
#define red 30
#define green 39
#define blue 40


//Pines de jugador 1
#define J1L1 PB_5
#define J1L2 PB_0
#define J1L3 PB_1
#define J1L4 PE_4
#define J1L5 PE_5
#define J1L6 PB_4
#define J1L7 PA_5
#define J1L8 PA_6

//Pines jugador 2
#define J2L1 PD_0
#define J2L2 PB_6
#define J2L3 PD_1
#define J2L4 PB_7
#define J2L5 PD_2
#define J2L6 PD_3
#define J2L7 PE_1
#define J2L8 PE_2

// Antirrebote

unsigned char banboton1;
unsigned char banboton2;

//contadores
unsigned char contador1;
unsigned char contador2;

//mostrar contador decada
char mcontador1;
char mcontador2;

//conteo de ganadas
unsigned char ganadas1;
unsigned char ganadas2;
//mostrar datos de jugadores
unsigned char banderadatos;
// Dar inicio al juego
unsigned char inicio;





void setup() {
  // put your setup code here, to run once:
  pinMode(jugador1, INPUT_PULLUP);
  pinMode(jugador2, INPUT_PULLUP);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  Serial.begin(9600);

  //valores iniciales
  inicio = 0;

  analogWrite(red, 255);
  contador1 = 0;
  contador2 = 0;
  mcontador1 = 0;
  mcontador2 = 0;
  ganadas1 = 0;
  ganadas2 = 0;
  banderadatos = 0;


  pinMode(J1L1 , OUTPUT);//CONFIGURAMOS COMO SALIDA LOS PINES
  pinMode(J1L2 , OUTPUT);
  pinMode(J1L3 , OUTPUT);
  pinMode(J1L4 , OUTPUT);
  pinMode(J1L5 , OUTPUT);
  pinMode(J1L6 , OUTPUT);
  pinMode(J1L7 , OUTPUT);
  pinMode(J1L8 , OUTPUT);


  pinMode(J2L1 , OUTPUT);
  pinMode(J2L2 , OUTPUT);
  pinMode(J2L3 , OUTPUT);
  pinMode(J2L4 , OUTPUT);
  pinMode(J2L5 , OUTPUT);
  pinMode(J2L6 , OUTPUT);
  pinMode(J2L7 , OUTPUT);
  pinMode(J2L8 , OUTPUT);



}

void loop() {





  //inicio con semaforo
  if (inicio == 0 ) {

    if (digitalRead(jugador1) == LOW and digitalRead(jugador2) == LOW) {
      banboton1 = 1;
    }
    else if ((digitalRead(jugador1) == HIGH and digitalRead(jugador2) == HIGH) && banboton1 == 1 ) {

      delay(1000);
      for (unsigned char i; i < 20; i++) {
        Serial.println();
      }
      analogWrite(red, 255);//rojo
      analogWrite(green, 0);
      analogWrite(blue, 0);
      Serial.println("Preparados!?");
      delay(1000);
      analogWrite(red, 255);//amarillo
      analogWrite(green, 248);
      analogWrite(blue, 7);
      Serial.println("Listos!?");
      delay(1000);
      analogWrite(red, 0);//verde
      analogWrite(green, 255);
      analogWrite(blue, 0);
      Serial.println("yaaaaaaaaaaaaaaaaaaaa!!!!!!!!!!!!!!!!!!!");
      for (unsigned char i; i < 10; i++) {
        Serial.println();
      }

      banboton1 = 0;
      banderadatos = 1;
      inicio = 1;

    }

  } else if (inicio == 1) {// Si el juego empezo

    resultado(contador1, &mcontador1);// segun contadores cambia el valor a ser impreso
    resultado(contador2, &mcontador2);

    if (banderadatos) {

      Serial.print("Jugador 1: ");
      Serial.print(mcontador1);
      Serial.print("   ");
      Serial.print("  Jugador 2: ");
      Serial.println(mcontador2);


      PORTA(mcontador1);
      PORTB(mcontador2);
      
    }

    if (digitalRead(jugador1) == LOW) {//boton jugador1 con antirrebote
      banboton1 = 1;
    }
    else if (digitalRead(jugador1) == HIGH && banboton1 == 1) {
      contador1++;
      if (contador1 > 8) {
        contador1 = 8;
      }
      banboton1 = 0;
    }

    if (digitalRead(jugador2) == LOW) {//boton jugador 2 con antirrebote

      banboton2 = 1;
    }
    else if (digitalRead(jugador2) == HIGH && banboton2 == 1) {
      contador2++;
      if (contador2 > 8) {
        contador2 = 8;
      }
      banboton2 = 0;
    }

    if (contador1 == 8 or contador2 == 8) {// verificar si alguna ya gano y luego ver quien fue
      for (unsigned char i; i < 5; i++) {
        Serial.println();
      }
      Serial.println("--------------------------------------------------------------------------------");
      Serial.println("Los resultados son:");
      Serial.print("jugador 1: ");
      Serial.print(contador1);
      Serial.print("  jugador 2: ");
      Serial.println(contador2);
      banderadatos = 0;


      if (contador1 > contador2 ) {// Si gano jugador 1

        Serial.println("Claramente gano jugador 1");
        ganadas1++;
        analogWrite(red, 0);
        analogWrite(green, 26);//azul
        analogWrite(blue, 255);

      } else if (contador1 < contador2) { // si gano el jugador 2

        Serial.println("Claramente gano jugador 2");
        ganadas2++;
        analogWrite(red, 255);
        analogWrite(green, 0);//morado
        analogWrite(blue, 222);
      }


      Serial.println("");// Imprimir las veces que cada uno ha ganado
      Serial.print("Jugador 1 ha ganado: ");
      Serial.print(ganadas1);
      Serial.println(" veces");
      Serial.print("Jugador 2 ha ganado: ");
      Serial.print(ganadas2);
      Serial.println(" veces");
      contador1 = 0;
      contador2 = 0;
      inicio = 0;



    }



  }
}

void resultado (unsigned char valor1, char *valor2) {// Rutina para el contador de decada
  switch (valor1) {
    case (0): *valor2 = B00000000; break;// ASIGNAMOS VALOR BINARIO A VARIABLE
    case (1): *valor2 = B10000000; break;
    case (2): *valor2 = B01000000; break;
    case (3): *valor2 = B00100000; break;
    case (4): *valor2 = B00010000; break;
    case (5): *valor2 = B00001000; break;
    case (6): *valor2 = B00000100; break;
    case (7): *valor2 = B00000010; break;
    case (8): *valor2 = B00000001; break;
  }

}
void PORTA(unsigned char valor) { // mostrar valores en LEDS JUGADOR 2

  if (valor & B10000000) {
    digitalWrite(J1L1, HIGH);
  } else  {
    digitalWrite(J1L1, LOW);
  }
  if (valor & B01000000) {
    digitalWrite(J1L2, HIGH);
  } else  {
    digitalWrite(J1L2, LOW);
  }
  if (valor & B00100000) {
    digitalWrite(J1L3, HIGH);
  } else  {
    digitalWrite(J1L3, LOW);
  }
  if (valor & B00010000) {
    digitalWrite(J1L4, HIGH);
  } else  {
    digitalWrite(J1L4, LOW);
  }
  if (valor & B00001000) {
    digitalWrite(J1L5, HIGH);
  } else  {
    digitalWrite(J1L5, LOW);
  }
  if (valor & B00000100) {
    digitalWrite(J1L6, HIGH);
  } else  {
    digitalWrite(J1L6, LOW);
  }
  if (valor & B00000010) {
    digitalWrite(J1L7, HIGH);
  } else {
    digitalWrite(J1L7, LOW);
  }
  if (valor & B00000001) {
    digitalWrite(J1L8, HIGH);
  } else  {
    digitalWrite(J1L8, LOW);
  }

}

void PORTB(unsigned char valor) { // mostrar valores en LEDS JUGADOR 2

  if (valor & B10000000) {
    digitalWrite(J2L1, HIGH);
  } else  {
    digitalWrite(J2L1, LOW);
  }
  if (valor & B01000000) {
    digitalWrite(J2L2, HIGH);
  } else  {
    digitalWrite(J2L2, LOW);
  }
  if (valor & B00100000) {
    digitalWrite(J2L3, HIGH);
  } else  {
    digitalWrite(J2L3, LOW);
  }
  if (valor & B00010000) {
    digitalWrite(J2L4, HIGH);
  } else  {
    digitalWrite(J2L4, LOW);
  }
  if (valor & B00001000) {
    digitalWrite(J2L5, HIGH);
  } else  {
    digitalWrite(J2L5, LOW);
  }
  if (valor & B00000100) {
    digitalWrite(J2L6, HIGH);
  } else  {
    digitalWrite(J2L6, LOW);
  }
  if (valor & B00000010) {
    digitalWrite(J2L7, HIGH);
  } else {
    digitalWrite(J2L7, LOW);
  }
  if (valor & B00000001) {
    digitalWrite(J2L8, HIGH);
  } else  {
    digitalWrite(J2L8, LOW);
  }

}
