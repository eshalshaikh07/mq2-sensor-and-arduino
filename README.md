# Arduino Vegetable and Fruit Rotting Detector

This Arduino program uses an MQ-2 methane sensor to detect methane levels, which can indicate the rotting of vegetables and fruits. The detected methane levels are displayed on an LCD screen, and an LED and buzzer are activated if a drastic change in methane levels is detected.

## Features

- Detects methane levels using an MQ-2 sensor.
- Displays methane levels on a 16x2 I2C LCD.
- Activates an LED and buzzer if a significant change in methane levels is detected, indicating rotting.

## Components

- Arduino board (e.g., Uno, Nano)
- MQ-2 methane sensor
- 16x2 I2C LCD display
- LED
- Buzzer
- Jumper wires
- Breadboard

## Circuit Diagram

1. **MQ-2 Methane Sensor**:
   - VCC to 5V
   - GND to GND
   - AO to A1 (Analog pin)

2. **LCD Display**:
   - SDA to A4 (or corresponding I2C pin)
   - SCL to A5 (or corresponding I2C pin)
   - VCC to 5V
   - GND to GND

3. **LED**:
   - Anode to digital pin 2
   - Cathode to GND (through a current-limiting resistor)

4. **Buzzer**:
   - Positive to digital pin 3
   - Negative to GND

## Code

### Arduino Sketch

```cpp
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
