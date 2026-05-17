// SENSOR

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 14 // No NodeMCU é o pino D5, que corresponde ao GPIO14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    delay(2000);
    
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    if (isnan(temperatura) || isnan(umidade)) {
        Serial.println("Erro lendo DHT11");
        return;
    }

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" - Umidade: ");
    Serial.println(umidade);
}
