#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int SERVO_PIN = 9;
int positionPercent = 50;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(19, OUTPUT); // GREEN LED pin (Reaction time)
  pinMode(21, INPUT); // Reaction time button
  pinMode(SERVO_PIN, OUTPUT);
  Wire.begin(4, 5); // sda = 4, sdk = 5
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the backlight

  Serial.begin(115200);
}
// ------------------------------------------------------------------------------------------------
unsigned long avgReactionTime = 0;
void setReactionTime() {
  lcd.setCursor(0, 0); 
  lcd.print("Click to start");
  while(!digitalRead(21)){
    // do nothing
  }
  lcd.clear();
  lcd.print("Testing avg reaction");
  unsigned long startTime; // Var to store the startTime of the LED
  digitalWrite(19, LOW); // intially set LED to low
  for (int i = 0; i < 5; i++) { // 5 trials taken to average reaction time
    lcd.setCursor(0, 1); 
    lcd.print("Trial: " + String(i+1) + "/5");
    delay(1000); // wait at least 1 second, random from 1-2.999 seconds.
    delay((uint32_t) random(2000));
    digitalWrite(19, HIGH); // Turn LED on the first time
    startTime = millis(); // set startTime;
    while(!digitalRead(21)) {
      // do nothing, wait for input
    }
    avgReactionTime += millis() - startTime; // sum differences in time to avgReactionTime;
    digitalWrite(19, LOW);
  }
  avgReactionTime /= 5; //actually average the reaction time;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Average Reaction:");
  lcd.setCursor(0, 1);
  lcd.print(String(avgReactionTime) + "ms");
  delay(4000);
  lcd.clear();
}
// ------------------------------------------------------------------------------------------------
void testReactionTime() {
  lcd.setCursor(0, 0); 
  lcd.print("Click to start");
  while(!digitalRead(21)){
    // do nothing
  }
  lcd.clear();
  lcd.print("Testing real reaction");
  unsigned long startTime; // Var to store the startTime of the LED
  unsigned long totalTime = 0; // Var to store the total reaction time
  digitalWrite(19, LOW); // intially set LED to low
  delay(1000); // wait at least 1 second, random from 1-2.999 seconds.
  delay((uint32_t) random(2000));
  digitalWrite(19, HIGH); // Turn LED on the first time
    startTime = millis(); // set startTime;
  while(!digitalRead(21)) {
      // do nothing, wait for input
  }
  totalTime = millis() - startTime;
  digitalWrite(19, LOW);
  delay(300);
  lcd.clear();
  if (totalTime <= (1.25 * avgReactionTime)) { // alcohol at legal limit slows ur reaction time by about 15-20%, so the test is passed if the reaction taken is less than 1.25*avgReactionTime.
    lcd.print("Passed reaction test!");
    digitalWrite(19, HIGH);
    delay(500);
    digitalWrite(19, LOW);
    delay(500);
    digitalWrite(19, HIGH);
    delay(500);
    digitalWrite(19, LOW);
    delay(500);
    digitalWrite(19, HIGH);
    delay(500);
    digitalWrite(19, LOW);
  } else {
    lcd.print("Failed reaction test!");
  }
  lcd.clear();
}
// ------------------------------------------------------------------------------------------------
void lockServo() {
  positionPercent = 100;
  int pulseWidth = map(positionPercent, 0, 100, 1000, 2000);
  for (int i = 0; i < 100; i++) {
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pulseWidth);
  
    digitalWrite(SERVO_PIN, LOW);
  
    delayMicroseconds(20000 - pulseWidth);
  }
}

void unlockServo() {
  positionPercent = 0;
  int pulseWidth = map(positionPercent, 0, 100, 1000, 2000);
  for (int i = 0; i < 100; i++) {
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pulseWidth);
  
    digitalWrite(SERVO_PIN, LOW);
  
    delayMicroseconds(20000 - pulseWidth);
  }
}

void loop() {
  setReactionTime();
  testReactionTime();
}