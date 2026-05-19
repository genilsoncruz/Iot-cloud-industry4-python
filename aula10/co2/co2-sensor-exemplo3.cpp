#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "ESTACIO-VISITANTES";
const char* password = "estacio@2014"; 

const char* FIREBASE_URL = "https://smart-campus-iot-2bd80-default-rtdb.firebaseio.com/dados.json";

const int pwmPin = D5;

int ppm = 0;

// Protótipos das funções
void conectarWiFi();
void enviarDadosFirebase(String deviceName, float lat, float lng, float alt, float speed, int co2Ppm, long timestampUnix);

void setup() {

  Serial.begin(9600);
  pinMode(pwmPin, INPUT);
  conectarWiFi();

  Serial.println("Iniciando leitura do sensor SC8...");
}

void loop() {

  // Timeout ~1.1s
  unsigned long highTime =
    pulseIn(pwmPin, HIGH, 1100000);

  if (highTime > 0) {

    ppm =
      10000 * (highTime - 2000)
      / 1004000;

    Serial.print("CO2: ");
    Serial.print(ppm);
    Serial.println(" ppm");

    enviarDadosFirebase("SC8-device-001", -23.55052, -46.633308, 760.0, 0.0, ppm, millis() / 1000);

  } else {

    Serial.println(
      "Erro: sem pulso PWM"
    );
  }

  delay(2000);
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

void enviarDadosFirebase(String deviceName, float lat, float lng, float alt, float speed, int co2Ppm, long timestampUnix) {
  // Verifica se o ESP8266 continua conectado ao Wi-Fi antes de tentar enviar
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Erro: WiFi desconectado.");
    return;
  }

  WiFiClientSecure client;
  // O Firebase exige conexões seguras (HTTPS). 
  // Para fins de teste/simplificação, vamos ignorar a validação estrita do certificado SSL:
  client.setInsecure(); 

  HTTPClient http;

  Serial.println("Iniciando requisição POST para o Firebase...");
  
  // Inicializa a conexão com a URL do Firebase
  if (http.begin(client, FIREBASE_URL)) {
    
    // Define o cabeçalho informando que estamos enviando um JSON
    http.addHeader("Content-Type", "application/json");

    // Monta a String JSON respeitando exatamente a estrutura do script Python
    // Nota: Usamos \" para escapar as aspas duplas dentro da String C++
    String jsonPayload = "{";
    jsonPayload += "\"device\":\"" + deviceName + "\",";
    jsonPayload += "\"gps\":{";
    jsonPayload += "\"lat\":" + String(lat, 6) + ","; // 6 casas decimais para GPS
    jsonPayload += "\"lng\":" + String(lng, 6) + ",";
    jsonPayload += "\"alt\":" + String(alt, 1) + ",";
    jsonPayload += "\"speed\":" + String(speed, 1);
    jsonPayload += "},";
    jsonPayload += "\"co2\":{";
    jsonPayload += "\"ppm\":" + String(co2Ppm);
    jsonPayload += "},";
    jsonPayload += "\"timestamp\":" + String(timestampUnix);
    jsonPayload += "}";

    // Envia a requisição POST (equivalente ao requests.post do Python)
    int httpResponseCode = http.POST(jsonPayload);

    // Trata o retorno da requisição (equivalente ao raise_for_status())
    if (httpResponseCode > 0) {
      Serial.print("Sucesso! Código HTTP: ");
      Serial.println(httpResponseCode);
      
      String responseBody = http.getString();
      Serial.print("Resposta do Firebase: ");
      Serial.println(responseBody); // O Firebase costuma retornar a chave gerada pelo POST
    } else {
      Serial.print("Erro ao enviar POST. Código de erro: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    // Fecha a conexão e libera os recursos
    http.end();
  } else {
    Serial.println("Não foi possível conectar ao servidor.");
  }
}
