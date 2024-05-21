// defining constants
const int ldrPin = A0; // ADC pin for LDR
float voltage = 0;
float lux = 0;

void setup() {
  // initialize serial communication at 9600 bps
  Serial.begin(115200); 

  // setting PIN A0 as INPUT
  pinMode(ldrPin, INPUT);
}

void loop() {
  // read the analog value from the LDR
  voltage = analogRead(ldrPin) * (5.0 / 1023.0);
  lux = calculateLux(voltage);

  // send voltage and lux values to ESP32 via UART
  Serial.print(voltage);
  Serial.print(",");
  Serial.println(lux);
  
  delay(500); // delay for 5ms before next reading
}

// equation from IPYNB
float calculateLux(float x) {
  // polynomial equation coefficients for a 4th-degree polynomial
  if (x < 4.2) {
    // coefficients for LUX < 800
    return 6.52628248*pow(x, 4) + -19.21400838*pow(x, 3) + -67.11744997*pow(x, 2) + 260.06964618*x + -167.5903256;
  } else {
    // coefficients for LUX > 800
    return 2.61873989e+05*pow(x, 4) + -4.65486908e+06*pow(x, 3) + 3.10090126e+07*pow(x, 2) + -9.17484258e+07*x + 1.01727253e+08;
  }
}

          
  