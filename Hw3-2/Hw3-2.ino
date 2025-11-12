const int buttonPin = 2;   // 按鈕接在 D2
const int ledPin = 3;      // LED 接在 D3

int buttonState = HIGH;        // 目前按鈕狀態
int lastButtonState = HIGH;    // 上一次按鈕狀態
int mode = 0;                  // LED 模式（0～3）
unsigned long previousMillis = 0;
unsigned long interval = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // 按鈕使用內建上拉
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // 檢測按鈕從未按下 → 按下（避免重複觸發）
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50); // 消抖
    mode++;
    if (mode > 3) mode = 0; // 循環模式
  }
  lastButtonState = buttonState;

  unsigned long currentMillis = millis();

  // 根據模式控制 LED
  switch (mode) {
    case 0: // 恆亮
      digitalWrite(ledPin, HIGH);
      break;

    case 1: // 慢閃 (1 秒一次)
      interval = 1000;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, !digitalRead(ledPin));
      }
      break;

    case 2: // 中速閃 (0.5 秒一次)
      interval = 500;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, !digitalRead(ledPin));
      }
      break;

    case 3: // 快閃 (0.2 秒一次)
      interval = 200;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, !digitalRead(ledPin));
      }
      break;
  }
}

