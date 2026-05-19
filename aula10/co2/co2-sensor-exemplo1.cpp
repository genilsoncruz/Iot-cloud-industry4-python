#include <Arduino.h>

const int pwmPin = D5;

int ppm = 0;

void setup() {

  Serial.begin(9600);

  pinMode(pwmPin, INPUT);

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

  } else {

    Serial.println(
      "Erro: sem pulso PWM"
    );
  }

  delay(2000);
}
