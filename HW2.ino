const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int mood = 0;
const int neutralMood = 10;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;

int buttonState = 0;
bool buttonPressed = false;
const int buttonPin = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  Serial.begin(9600);

  mood = neutralMood;
}

void loop() {

  // 按下按鈕時增加心情值
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !buttonPressed) {
    mood = mood + 1;
    touchedTimer = millis();
    buttonPressed = true;
    if (mood > 20) mood = 20;
  }

  // 放開按鈕時重置狀態
  if (buttonState == LOW && buttonPressed) {
    buttonPressed = false;
  }

  // 若超過5秒未按按鈕，心情慢慢下降
  unsigned long currentMillis = millis();
  if (currentMillis - touchedTimer > 5000) {
    if (currentMillis - reducedTimer > 1000) {
      mood = mood - 1;
      if (mood < 0) mood = 0;
      reducedTimer = currentMillis;
    }
  }
  Serial.println(mood);
  showLEDState(mood);
}

void showLEDState(int state) {
  float EmotionControl = 255.0 / 10.0;

  if (state > neutralMood) {
    // 偏快樂 → 綠色減少、藍色亮度固定
    analogWrite(RledPin, 255);
    analogWrite(GledPin, EmotionControl * (state - neutralMood));
    analogWrite(BledPin, 255-EmotionControl * (state - neutralMood));
  }
  else {
    // 偏低落 → 紅色增加
    analogWrite(RledPin, 255 - EmotionControl * (neutralMood - state));
    analogWrite(GledPin, EmotionControl * (neutralMood - state));
    analogWrite(BledPin, 255);
  }
}
