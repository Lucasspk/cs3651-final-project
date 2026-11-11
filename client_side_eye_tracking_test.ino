const unsigned long BAUD_RATE = 115200;
const size_t LINE_BUFFER_SIZE = 64;

char lineBuffer[LINE_BUFFER_SIZE];
size_t lineLength = 0;

void processLine() {
  lineBuffer[lineLength] = '\0';

  float x, y;
  if (sscanf(lineBuffer, "%f,%f", &x, &y) == 2) {
    if (x == -1.0f && y == -1.0f) {
      Serial.println("Tracking lost");
    } else {
      Serial.printf("Received gaze: X=%.2f, Y=%.2f\n", x, y);
    }
  } else {
    Serial.printf("Invalid data: %s\n", lineBuffer);
  }

  lineLength = 0;
}

void setup() {
  Serial.begin(BAUD_RATE);   // Native USB, shown as COM4
  Serial0.begin(BAUD_RATE);  // UART0, connected to the other USB port / COM3

  Serial.println("Listening for gaze data on UART0...");
}

void loop() {
  while (Serial0.available() > 0) {
    char c = static_cast<char>(Serial0.read());

    if (c == '\n') {
      processLine();
    } else if (c != '\r') {
      if (lineLength < LINE_BUFFER_SIZE - 1) {
        lineBuffer[lineLength++] = c;
      } else {
        lineLength = 0;
        Serial.println("Input line too long; discarded");
      }
    }
  }
}