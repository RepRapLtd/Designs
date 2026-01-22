/*
  ESP32 GPIO oscillator test
  Type a GPIO number into Serial Monitor (newline-terminated).
  The selected GPIO will toggle at ~1 kHz until another number is entered.
*/

int currentPin = -1;
bool pinState = false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.println();
  Serial.println("GPIO oscillator test");
  Serial.println("Type a GPIO number and press Enter.");
  Serial.println("Example: 2");
}

void loop() {
  // Check for new GPIO number from serial
  if (Serial.available()) {
    int newPin = Serial.parseInt();

    // Flush rest of line
    while (Serial.available()) Serial.read();

    if (newPin >= 0) {
      // Turn off previous pin
      if (currentPin >= 0) {
        digitalWrite(currentPin, LOW);
        pinMode(currentPin, INPUT);
      }

      // Prepare new pin
      currentPin = newPin;
      digitalWrite(currentPin, LOW);   // set level before OUTPUT
      pinMode(currentPin, OUTPUT);
      pinState = false;

      Serial.print("Now oscillating GPIO ");
      Serial.println(currentPin);
    }
  }

  // Oscillate current pin at ~1 kHz
  if (currentPin >= 0) {
    pinState = !pinState;
    digitalWrite(currentPin, pinState ? HIGH : LOW);
    delayMicroseconds(500);
  } else {
    delay(10);
  }
}
