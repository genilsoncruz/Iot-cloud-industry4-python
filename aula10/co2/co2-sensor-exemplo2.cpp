const int pinoSensor = A0;

int valorLido = 0;

float tensao = 0;

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("MQ135 + ESP8266");
  Serial.println("Aquecendo sensor...");
  Serial.println("================================");

  // MQ135 precisa aquecer
  delay(30000);

  Serial.println("Sensor pronto!");
}

void loop() {

  long soma = 0;

  // Média de 100 leituras
  for (int i = 0; i < 100; i++) {

    soma += analogRead(pinoSensor);

    delay(5);
  }

  valorLido = soma / 100;

  // Conversão aproximada
  tensao =
    valorLido * (3.3 / 1023.0);

  Serial.println();

  Serial.print("Valor ADC: ");
  Serial.println(valorLido);

  Serial.print("Tensao: ");
  Serial.print(tensao);
  Serial.println(" V");

  // Percentual aproximado
  int qualidade =
    map(valorLido, 0, 1023, 100, 0);

  Serial.print("Qualidade do ar: ");
  Serial.print(qualidade);
  Serial.println("%");

  // Faixas simples
  if (valorLido < 250) {

    Serial.println(
      "✅ Ar limpo"
    );

  } else if (valorLido < 400) {

    Serial.println(
      "⚠️ Qualidade moderada"
    );

  } else if (valorLido < 700) {

    Serial.println(
      "⚠️ Ar poluido"
    );

  } else {

    Serial.println(
      "🚨 Alta concentracao de gases"
    );
  }

  Serial.println("------------------------");

  delay(2000);
}
