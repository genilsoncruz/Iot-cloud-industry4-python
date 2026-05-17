// Definindo o pino analógico conectado ao sensor
const int pinoSensor = A0; 
int valorLido = 0;

void setup() {
  // Inicializa a comunicação serial a 9600 bps
  Serial.begin(9600); 
  
  Serial.println("Aquecendo o sensor MQ-135...");
  // O sensor precisa de um tempo de pré-aquecimento para dar leituras estáveis
  delay(5000); 
}

void loop() {
  // Realiza a leitura do pino analógico (retorna de 0 a 1023)
  valorLido = analogRead(pinoSensor); 
  
  // Imprime o valor no Monitor Serial
  Serial.print("Valor Analógico Bruto: ");
  Serial.println(valorLido);
  
  // Lógica simples de alerta baseada no valor lido
  if (valorLido > 400) {
    Serial.println("⚠️ Alerta: Concentração de gás elevada / Ar poluído!");
  } else {
    Serial.println("✅ Qualidade do ar normal.");
  }
  
  // Aguarda 2 segundos antes da próxima leitura
  delay(2000); 
}
