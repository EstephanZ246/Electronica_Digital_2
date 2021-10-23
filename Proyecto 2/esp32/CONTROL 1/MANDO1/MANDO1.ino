#include <esp_now.h>
#include <WiFi.h>


unsigned char up;
unsigned char down;
unsigned char jump;
unsigned char luz;
unsigned char extra;

unsigned char rebote_up;
unsigned char rebote_down;
unsigned char rebote_jump;
unsigned char rebote_jump1;
unsigned char rebote_luz;
unsigned char rebote_extra;
unsigned char contador;

#define RB0 35// pines de los botones
#define RB1 32
#define RB2 34
#define RB3 33
#define RB4 25

#define RA0 26


uint8_t broadcastAddress[] = {0x9C, 0x9C, 0x1F, 0xCA, 0x82, 0x94}; // 9C:9C:1F:CA:82:94   DIRECCION MAC DE LA TIVA 1
int enviar;

void setup() {

  //pines IO

  pinMode(RB0, INPUT);
  pinMode(RB1, INPUT);
  pinMode(RB2, INPUT);
  pinMode(RB3, INPUT);
  pinMode(RB4, INPUT);
  pinMode(RA0, OUTPUT);


  Serial.begin(115200);


  WiFi.mode(WIFI_STA);

  //Serial.println();
  //Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // register peer
  esp_now_peer_info_t peerInfo;

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // send data


  //esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &x, sizeof(int));

  /* if (result == ESP_OK) {
     Serial.println("Sent with success");
    }
    else {
     Serial.println("Error sending the data");
    }*/

}

void loop() {


 // esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &enviar, sizeof(int));


  if (digitalRead(RB0) == LOW) {
    rebote_up = 1;
  } else if (digitalRead(RB0) == HIGH && rebote_up == 1) {
    enviar = 'U';
    Serial.print('U');
    rebote_up = 0;
  }
  if (digitalRead(RB1) == LOW) {
    rebote_down = 1;
  } else if (digitalRead(RB1) == HIGH && rebote_down == 1) {
    enviar = 'D';
    Serial.print('D');
    rebote_down = 0;
  }
  if (digitalRead(RB2) == LOW) {
    rebote_jump = 1;
    if (rebote_jump1 == 1){
    enviar = 'P';
    Serial.print('P');
    rebote_jump1 = 0;
    }
  } else if (digitalRead(RB2) == HIGH && rebote_jump == 1) {
    enviar = 'I';
    Serial.print('I');
    rebote_jump1 = 1;
    rebote_jump = 0;
  }
  if (digitalRead(RB3) == LOW) {
    rebote_luz = 1;
  } else if (digitalRead(RB3) == HIGH && rebote_luz == 1) {
   // digitalWrite(RA0) = digitalWrite(RA0) ^ 1;
    rebote_luz = 0;
  }
 /* if (digitalRead(RB4) == LOW) {
    rebote_extra = 1;
    
  } else if (digitalRead(RB4) == HIGH && rebote_extra == 1) {

    enviar = 'M';
    Serial.print('M');
    rebote_extra = 0;
  }
*/
  if (enviar != 0){
    esp_now_send(broadcastAddress, (uint8_t *) &enviar, sizeof(int));
    enviar = 0;
  }







}
