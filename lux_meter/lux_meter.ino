const int ldrPin = 36; // ADC1 channel 0 (GPIO36) for ESP32

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int analogValue = analogRead(ldrPin)/4; // Read the analog value from the LDR
  float lux = calculateLux(analogValue);  // Calculate light intensity in lux using the polynomial equation

  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Light Intensity: ");
  Serial.print(lux, 4); // Print lux with 4 decimal places
  Serial.println(" lux");

  delay(1000); // Wait for a second before taking another reading
}

float calculateLux(int x) {
  // Polynomial equation coefficients for a 4th-degree polynomial
  float lux;

  if (x < 800) {
    // Coefficients for LUX < 800
    const float a4 = 3.17382282e-09;
    const float a3 = -1.70265352e-06;
    const float a2 = -1.43694567e-03;
    const float a1 = 1.02943685;
    const float a0 = -132.143469;

    lux = a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
  } else {
    // Coefficients for LUX > 800
    const float a4 = 1.49971935e-04;
    const float a3 = -5.45547466e-01;
    const float a2 = 7.43741376e+02;
    const float a1 = -4.50342742e+05;
    const float a0 = 1.02186631e+08;

    lux = a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
  }

  return lux;
}
