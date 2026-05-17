// SENSOR + WIFI + ENVIO PARA GOOGLE SHEETS

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

const char* ssid = "ESTACIO-VISITANTES";
const char* password = "estacio@2014"; // Se a rede tiver senha, insira aqui

const char* googleScriptURL = "https://script.google.com/macros/s/AKfycbyBCZ6netUiDLVm9q9Auj8gmX2dUqWL-qSZ8ej_RsNgn5BCQWNh88dCK147oG0YU__m/exec";

#define DHTPIN 14 // No NodeMCU é o pino D5, que corresponde ao GPIO14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Protótipos das funções
void conectarWiFi();
void enviarDados(float temperatura, float umidade);

void setup() {
    Serial.begin(115200);
    dht.begin();
    conectarWiFi();
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

    enviarDados(temperatura, umidade);

    Serial.println("----------------------");
    delay(15000); // Aumentado para 15s para evitar spam no Google Scripts
}

void conectarWiFi() {
    Serial.print("Conectando ao WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado!");
}

void enviarDados(float temperatura, float umidade) {
    WiFiClientSecure client;
    HTTPClient http;

    // Configuração crucial para HTTPS no ESP8266
    client.setInsecure(); // Ignora a verificação de certificado SSL para economizar memória
    
    // No ESP8266, o begin precisa do 'client' antes da URL
    if (http.begin(client, googleScriptURL)) {
        // Habilita seguir o redirecionamento (essencial para Google Apps Script)
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        
        http.addHeader("Content-Type", "application/json");

        String json = "{\"temperatura\":" + String(temperatura, 2) + 
                      ",\"umidade\":" + String(umidade, 2) + "}";

        Serial.print("Enviando JSON: ");
        Serial.println(json);

        int httpCode = http.POST(json);

        if (httpCode > 0) {
            Serial.printf("HTTP Code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                String resposta = http.getString();
                Serial.println("Resposta do Servidor: " + resposta);
            }
        } else {
            Serial.printf("Falha na requisição: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    } else {
        Serial.println("Não foi possível conectar ao servidor");
    }
}
