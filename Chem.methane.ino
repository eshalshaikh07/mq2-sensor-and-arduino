#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED 2
#define Buzzer 3
#define MethaneSensor A1 // Analog pin for methane sensor

int previousMethaneValue = 0; // Variable to store the previous methane value

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  int methaneValue = analogRead(MethaneSensor);
  lcd.setCursor(0, 0);
  lcd.print("Methane:");
  lcd.print(methaneValue);

  if (abs(methaneValue - previousMethaneValue) > 120) { // Check for a drastic change (adjust threshold as needed)
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("rotting!");
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, LOW);
    lcd.setCursor(0, 1);
    lcd.print("                           ");
  }

  previousMethaneValue = methaneValue; // Update previous value

  delay(1000); // Adjust delay as needed for stability
}
