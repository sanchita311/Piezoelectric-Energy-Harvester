#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Constants
int prev = 0, stepCount = 0;
unsigned long previousMillis = 0;
const long interval = 1000;  
unsigned long currentMillis;

float v, vout, vin;  // Variables for calculating voltage

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  pinMode(8, OUTPUT); // LED indication
  pinMode(9, OUTPUT); // Buzzer control

  lcd.init();
  lcd.backlight();

  lcd.print("FOOT STEP POWER");
  lcd.setCursor(0, 1);
  lcd.print("   GENERATOR");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("STEP COUNT:");
  lcd.setCursor(0, 1);
  lcd.print("VOLTAGE:");
}

void loop() {
  v = analogRead(A0);
  currentMillis = millis();

  if (v != 0 && prev == 0) {
    stepCount += 1;
    digitalWrite(8, HIGH); // LED ON
    digitalWrite(9, HIGH); // Buzzer ON

    lcd.setCursor(12, 0);
    lcd.print(stepCount);
  } else {
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      digitalWrite(8, LOW);  // LED OFF
      digitalWrite(9, LOW);  // Buzzer OFF
    }
  }

  prev = v;

  // Voltage calculation
  lcd.setCursor(9, 1);
  vout = (v * 5.00) / 1024.00;
  vin = (vout / 0.040909) * 100;

  lcd.print(vin);
  lcd.print("mV ");
  delay(200);
}
