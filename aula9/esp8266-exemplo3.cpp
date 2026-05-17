#include <Arduino.h>

void setup() {
    // Inicializa a serial em alta velocidade para não gargalar o processamento
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n--- TESTE DE PERFORMANCE ESP8266 ---");
}

bool ehPrimo(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void loop() {
    unsigned long tempoInicial = micros(); // Medição em microssegundos para precisão
    int totalPrimos = 0;
    int limite = 10000;

    Serial.println("Calculando números primos de 2 a 10.000...");

    for (int i = 2; i <= limite; i++) {
        if (ehPrimo(i)) {
            totalPrimos++;
        }
    }

    unsigned long tempoFinal = micros();
    unsigned long duracao = tempoFinal - tempoInicial;

    // Resultados
    Serial.print("Resultado: ");
    Serial.print(totalPrimos);
    Serial.println(" números primos encontrados.");
    
    Serial.print("Tempo de processamento: ");
    Serial.print(duracao / 1000.0, 3); // Converte para milissegundos com 3 casas decimais
    Serial.println(" ms");

    Serial.print("Velocidade média por cálculo: ");
    Serial.print((float)duracao / limite, 4);
    Serial.println(" microssegundos");
    
    Serial.println("------------------------------------");

    delay(5000); // Aguarda 5 segundos para a próxima demonstração
}
