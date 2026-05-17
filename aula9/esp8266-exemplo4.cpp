// 1. Esquema de Ligação e Pré-requisitos
// O ESP8266 trabalha com lógica de 3.3V. Um LED comum (vermelho, por exemplo) opera entre 1.8V e 2.0V. Se você ligá-lo direto, ele receberá corrente demais.
// Componentes necessários:
// 1 LED (Qualquer cor).
// 1 Resistor de $220\Omega$ a $330\Omega$: Serve para limitar a corrente e proteger o LED.
// Jumpers (fios) e uma Protoboard.
// Conexão Física:
// Anodo (Perna longa do LED): Conecte em uma extremidade do resistor.
// Outra extremidade do resistor: Conecte ao pino D6 (GPIO 12) do NodeMCU.
// Catodo (Perna curta do LED): Conecte ao pino GND (G) do NodeMCU.

#include <Arduino.h>

// No NodeMCU v2, o LED integrado geralmente está no pino D4 (GPIO 2)
#define LED_PIN 2

void setup() {
    // Configura o pino como saída
    pinMode(LED_PIN, OUTPUT);
    
    // Inicializa a Serial para o Olá Mundo textual
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n-----------------------");
    Serial.println("  OLA MUNDO ESP8266!   ");
    Serial.println("-----------------------");
}

void loop() {
    // Liga o LED (Nota: No ESP8266, LOW costuma ligar o LED interno)
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED Aceso!  (Status: LOW)");
    delay(500);

    // Desliga o LED
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED Apagado! (Status: HIGH)");
    delay(500);
}
