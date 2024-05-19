const int ldrPin = A0; // Analog pin connected to LDR

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int analogValue = analogRead(ldrPin); // Read the analog value from the LDR
  float lux = calculateLux(analogValue); // Calculate light intensity in lux using the given equation

  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Light Intensity: ");
  Serial.print(lux);
  Serial.println(" lux");

  delay(1000); // Wait for a second before taking another reading
}

float calculateLux(int x) {
  // Polynomial equation coefficients (example for a 4th-degree polynomial)
  float a4 = -1.05412039e-11;
  float a3 = 7.54032268e-08;
  float a2 = -1.98483678e-04;
  float a1 = 2.36418983e-01;
  float a0 = -1.07335165e+02;

  // Calculate lux using the polynomial equation
  float lux = a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
  return lux;
}
