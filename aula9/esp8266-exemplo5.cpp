#include <Arduino.h>
#include "thingProperties.h" // Arquivo gerado pelo Arduino Cloud com as credenciais

#define LED_PIN 12 // Corresponde ao D6

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Inicializa as propriedades e a conexão
  initProperties(); 
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

// Esta função é chamada automaticamente quando você muda o botão no Dashboard
void onLedStatusChange()  {
  if (led_status) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED Ligado via Cloud");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED Desligado via Cloud");
  }
}
