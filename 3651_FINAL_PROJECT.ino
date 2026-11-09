#include <Servo.h>
Servo myServo; // servo object
void setup() {
  myServo.attach(9);
  pinMode(19, OUTPUT); // GREEN LED pin (Reaction time)
  pinMode(21, INPUT); // Reaction time button
}
// ------------------------------------------------------------------------------------------------
unsigned long avgReactionTime = 0;
void setReactionTime() {
  unsigned long startTime; // Var to store the startTime of the LED
  digitalWrite(19, LOW); // intially set LED to low
  for (int i = 0; i < 5; i++) { // 5 trials taken to average reaction time
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
}
// ------------------------------------------------------------------------------------------------
void testReactionTime() {
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
  if (totalTime <= (1.25 * avgReactionTime)) { // alcohol at legal limit slows ur reaction time by about 15-20%, so the test is passed if the reaction taken is less than 1.25*avgReactionTime.
    // PASS
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
    // FAIL
  }
}
// ------------------------------------------------------------------------------------------------
void lockServo() {
  myServo.write(0);
  delay(1000);
}
void unlockServo() {
  myServo.write(180);
  delay(1000);
}

void loop() {
  lockServo();
  unlockServo();
}
