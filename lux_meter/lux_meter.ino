const int ldrPin = A0; // Analog pin connected to LDR

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int analogValue = analogRead(ldrPin); // Read the analog value from the LDR
  float lux = calculateLux(analogValue); // Calculate light intensity in lux using the polynomial equation

  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Light Intensity: ");
  Serial.print(lux);
  Serial.println(" lux");

  delay(1000); // Wait for a second before taking another reading
}

float calculateLux(int x) {
  // Polynomial equation coefficients for a 4th-degree polynomial
  float a4 = 1.49971935e-04;
  float a3 = -5.45547466e-01;
  float a2 = 7.43741376e+02;
  float a1 = -4.50342742e+05;
  float a0 = 1.02186631e+08;

  // Calculate lux using the polynomial equation
  float lux = a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
  return lux;
}
