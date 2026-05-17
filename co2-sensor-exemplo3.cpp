#include <SoftwareSerial.h>

// Define pins for Software Serial
const byte RX_PIN = 10; // Connects to sensor TX
const byte TX_PIN = 11; // Connects to sensor RX
SoftwareSerial sensorSerial(RX_PIN, TX_PIN);

// Standard Modbus request frame for SC8/S8 to read CO2
byte readCO2[] = {0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, 0xD5, 0xC5};
byte response[7];

void setup() {
  Serial.begin(9600);
  sensorSerial.begin(9600);
  Serial.println("SC8 CO2 Sensor Initialized...");
}

void loop() {
  // Send the request command
  for (int i = 0; i < 8; i++) {
    sensorSerial.write(readCO2[i]);
  }
  
  // Wait for a response
  delay(1000);

  // Read the response from the sensor
  if (sensorSerial.available() >= 7) {
    for (int i = 0; i < 7; i++) {
      response[i] = sensorSerial.read();
    }

    // Extract the High and Low bytes for CO2 PPM
    int high = response[3];
    int low = response[4];
    unsigned int co2_ppm = (high << 8) | low;

    // Print reading
    Serial.print("CO2 Level: ");
    Serial.print(co2_ppm);
    Serial.println(" ppm");
  } else {
    Serial.println("Waiting for sensor data...");
  }

  delay(5000); // Read every 5 seconds
}
