#include <Arduino.h>

void setup() {
  // Inicializa a comunicação serial a 115200 bits por segundo
  Serial.begin(115200);
  
  // Aguarda um segundo para garantir que a conexão serial estabilizou
  delay(1000);

  // O "Olá Mundo" clássico impresso apenas uma vez
  Serial.println("\n============================");
  Serial.println("Hello, World! Olá, Mundo!");
  Serial.println("ESP8266 pronto para uso.");
  Serial.println("============================\n");
}

void loop() {
  // Mantemos o loop enviando um sinal de vida a cada 5 segundos
  Serial.print("O sistema está rodando há: ");
  Serial.print(millis() / 1000);
  Serial.println(" segundos.");
  
  delay(5000);
}
