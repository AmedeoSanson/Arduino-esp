int stato = 0;
int led = 3;
int pulsante = 2;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pulsante, INPUT);
}

void loop() {
  switch (stato) {
    case 0:
      loop0();
      break;
    case 1:
      loop1();
      break;
    case 2:
      loop2();
      break;
    case 3:
      loop3();
      break;
  }
}
void loop0() {
  digitalWrite(led, LOW);
  if (digitalRead(pulsante)) {
    stato = stato + 1;
    delay(300);
  }
}
void loop1() {
  digitalWrite(led, HIGH);
  if (digitalRead(pulsante)) {
    stato = stato + 1;
    delay(300);
  }
}
unsigned long t0, dt = 0;
int statoled = LOW;
void loop2() {
  dt = millis() - t0;
  if (dt >= 500) {
    statoled = !statoled;
    digitalWrite(led, statoled);
    t0 = millis();
    if (digitalRead(pulsante)) {
      stato = stato + 1;
      delay(300);
    }
  }
}
void loop3() {
  analogWrite(led, 100);
  if (digitalRead(pulsante)) {
    stato = 0;
    delay(300);
  }
}
