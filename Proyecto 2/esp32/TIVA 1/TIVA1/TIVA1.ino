#include <esp_now.h>
#include <WiFi.h>

int recibido;


void onReceiveData(const uint8_t *mac, const uint8_t *data, int len) {

  // Serial.print("Received from MAC: ");

  /*for (int i = 0; i < 6; i++) {

    // Serial.printf("%02X", mac[i]);
    //if (i < 5)Serial.print(":");
    }*/

  int * messagePointer = (int*)data;

 // Serial.println();
 // Serial.println(*messagePointer);
  recibido = *messagePointer;

}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


}

void loop() {

  esp_now_register_recv_cb(onReceiveData);
  if (recibido > 0){

  if (recibido == 'U') {
    Serial2.print('U');
  }
  else if (recibido == 'D') {
    Serial2.print('D');
  }
  else if (recibido == 'P') {
    Serial2.print('P');
  }
  else if (recibido == 'I') {
    Serial2.print('I');
  }
  else if (recibido == 'N') {
    Serial2.print('N');
  } else if (recibido == 'M') {
    Serial2.print('M');
  }
  recibido = 0;
}
}
