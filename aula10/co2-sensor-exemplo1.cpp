const int pwmPin = 9;  // Pino conectado ao pino PWM do sensor SC8
int ppm = 0;           // Variável para armazenar a concentração de CO2

void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, INPUT);
  Serial.println("Iniciando leitura do sensor SC8...");
}

void loop() {
  // Lê a duração do pulso em nível alto (HIGH) em microssegundos
  // O período total do PWM do SC8 é de 1004 ms (1004000 microssegundos)
  unsigned long highTime = pulseIn(pwmPin, HIGH, 1050000);
  
  // Fórmula: PPM = 10000 * (Thigh - 2ms) / 1004ms
  // Subtraímos 2000 microssegundos (2ms) do tempo alto e dividimos pelo período total
  if (highTime > 0) {
    ppm = 10000 * (highTime - 2000) / 1004000;
    
    Serial.print("Concentracao de CO2: ");
    Serial.print(ppm);
    Serial.println(" PPM");
  } else {
    Serial.println("Erro: Sensor nao conectado ou sem pulso detectado.");
  }

  delay(2000); // Aguarda 2 segundos entre as leituras
}
