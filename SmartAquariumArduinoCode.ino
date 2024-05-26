#include <LiquidCrystal.h> // for LCD
#include <Servo.h> // for Servo

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // initialize LCD
Servo servo1; // initialize Servo
int pos = 0; // Servo position
int sensorPin = A0; // Temperature sensor pin (using A0 as it is an analog pin)

void readTemperature() {
  int reading = analogRead(sensorPin);
  float voltage = reading * 4.68 / 1024.0;
  float temperatureC = (voltage - 0.5) * 100;

  lcd.setCursor(0, 0);
  lcd.print("Celcius: ");
  lcd.print(temperatureC);
  delay(100);
}

void repeatReadTemperature(int times, int interval) {
  for (int i = 0; i < times; i++) {
    readTemperature();
    delay(interval);
  }
}

void rotateServo() {
  for (pos = 0; pos <= 180; pos++) {
    servo1.write(pos);
    delay(10);
  }
  delay(1000); // hold the servo open
  for (pos = 180; pos >= 0; pos--) {
    servo1.write(pos);
    delay(10);
  }
  delay(1000); // hold the servo closed
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  servo1.attach(7); // attach servo to pin 7
}

void loop() {
  repeatReadTemperature(5, 1000); // Read temperature every second for 5 seconds
  rotateServo(); // Rotate the servo
}
