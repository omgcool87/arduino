const int buttonPin = 2; // pushbutton pin
const int RledPin = 3;   // Red pin
const int GledPin = 4;   // Green pin
const int BledPin = 5;   // Blue pin

int buttonState = 0;
int lastButtonState = 0; // 記錄前一次按鈕狀態，避免連續觸發
int ledcolor = 0;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // 偵測從 LOW -> HIGH 才換色
  if (buttonState == HIGH && lastButtonState == LOW) {
    ledcolor++;
    delay(100); // 去抖動
  }

  lastButtonState = buttonState;

  // 顏色控制
  if (ledcolor == 0) { // off
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1) { // red
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 2) { // green
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 3) { // blue
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 4) { // yellow (Red + Green)
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 5) { // purple (Red + Blue)
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 6) { // cyan (Green + Blue)
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 7) { // white (all)
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if(ledcolor ==8){
    ledcolor = 0;
  }
}
