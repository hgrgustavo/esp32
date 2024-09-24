const int trigPin = 31;
const int echoPin = 33;
const int ioPin = 52;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ioPin, INPUT);
  Serial.begin(300);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // triggering buzzer
  switch (distance) {
    case 10:
        tone(ioPin, 35, 3.0);

    case 25:
        tone(ioPin, 40, 4.0);

    case 30:
        tone(ioPin, 50, 2.0);
  }

  Serial.println(distance);
  delay(1000);
}
