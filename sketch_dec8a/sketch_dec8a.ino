#include <Servo.h>

Servo myServo;
String buffer = "";

void setup() {
  Serial.begin(9600);
  myServo.attach(8);
  myServo.write(90);   // posisi tengah
}

void loop() {
  // Baca data serial langsung di loop (lebih stabil daripada serialEvent)
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      processInput(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }
}

void processInput(String data) {
  data.trim(); // buang spasi / \r

  if (data.startsWith("<") && data.endsWith(">")) {
    data = data.substring(1, data.length() - 1);

    int commaIndex = data.indexOf(',');
    if (commaIndex > 0) {
      int x = data.substring(0, commaIndex).toInt();

      // Mapping normal (Python sudah mirror)
      int angle = map(x, 0, 640, 0, 180);
      angle = constrain(angle, 0, 180);

      myServo.write(angle);
    }
  }
}
