#include <Arduino.h>

void setup() {
    // Inicializa a serial. Usamos 115200 para garantir que a 
    // transmissão dos dados não atrase o processador.
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n========================================");
    Serial.println("   DEMONSTRACAO DE VELOCIDADE DO ESP8266");
    Serial.println("========================================");
}

void loop() {
    unsigned long contagem = 0;
    unsigned long tempoInicial = millis();

    // O processador ficara "preso" aqui por exatamente 1000 milissegundos
    // executando a operacao contagem++ o mais rápido que puder.
    while (millis() - tempoInicial < 1000) {
        contagem++;
    }

    // Exibição dos resultados
    Serial.print("Operacoes de soma realizadas em 1 segundo: ");
    Serial.println(contagem);

    // Noção de Grandeza
    float mhz_equivalente = (float)contagem / 1000000;
    Serial.print("Isso equivale a aproximadamente ");
    Serial.print(mhz_equivalente, 2);
    Serial.println(" milhoes de somas por segundo (MHz de processamento logico).");
    
    Serial.println("----------------------------------------");

    // Espera 3 segundos para repetir o teste
    delay(3000);
}
