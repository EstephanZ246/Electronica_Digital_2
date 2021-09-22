//Botones y led que se usaron
#define jugador1  31
#define jugador2  17
#define red 30
#define green 39
#define blue 40


// Antirrebote

unsigned char banboton1;
unsigned char banboton2;

//contadores
unsigned char contador1;
unsigned char contador2;

//mostrar contador decada
String mcontador1;
String mcontador2;

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
  mcontador1 = "";
  mcontador2 = "";
  ganadas1 = 0;
  ganadas2 = 0;
  banderadatos = 0;




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

void resultado (unsigned char valor1, String *valor2) {// Rutina para el contador de decada
  switch (valor1) {
    case (0): *valor2 = "00000000"; break;
    case (1): *valor2 = "10000000"; break;
    case (2): *valor2 = "01000000"; break;
    case (3): *valor2 = "00100000"; break;
    case (4): *valor2 = "00010000"; break;
    case (5): *valor2 = "00001000"; break;
    case (6): *valor2 = "00000100"; break;
    case (7): *valor2 = "00000010"; break;
    case (8): *valor2 = "00000001"; break;
  }

}
