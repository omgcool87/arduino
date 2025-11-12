const int buttonpin = 2;
const int RLEDpin = 9;
const int BLEDpin = 10;
const int GLEDpin = 11;

int buttonState = 0;
bool buttonpressed = false;
unsigned long pressingtime = 0;
const int intervaltime = 2000; 

int LEDNum = 0;
int RLEDcolor = 0;
int GLEDcolor = 0;
int BLEDcolor = 0;
int Rcurrentcolor = 0;
int Gcurrentcolor =  0;
int Bcurrentcolor =  0;

int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;

const int fadeAmount = 2;
int FadeDirection = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonpin, INPUT);
  pinMode(RLEDpin, OUTPUT);
  pinMode(BLEDpin, OUTPUT);
  pinMode(GLEDpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkbutton();
  updateLEDcolor();
  setRGBcolor(Rcurrentcolor , Gcurrentcolor , Bcurrentcolor);
}

void setRGBcolor(int r ,int g ,int b) {
  analogWrite(RLEDpin, r);
  analogWrite(GLEDpin, g);
  analogWrite(BLEDpin, b);
}

void checkbutton() {
  
  buttonState = digitalRead(buttonpin);

  if(buttonState==HIGH && !buttonpressed) {
      pressingtime = millis();
      buttonpressed = true;
    }

    if(buttonState==LOW && buttonpressed) {
      unsigned long currenttime = millis();
      if(currenttime - pressingtime < intervaltime) {
        Serial.println("short click");
        changeLED();
      }else {
        Serial.println("long click");
        changeMODE();
      }
    buttonpressed = false;
    }
}

void changeLED() {
  LEDNum++;
  if(LEDNum >= 5) {
    LEDNum = 0;
  }
  if(LEDNum == 0) {
    RLEDcolor = 0;
    GLEDcolor = 0;
    BLEDcolor = 0;
  }
  if(LEDNum == 1) {
    RLEDcolor = 0;
    GLEDcolor = 255;
    BLEDcolor = 255;
  }
  if(LEDNum == 2) {
    RLEDcolor = 255;
    GLEDcolor = 0;
    BLEDcolor = 255;
  }
  if(LEDNum == 3) {
    RLEDcolor = 255;
    GLEDcolor = 255;
    BLEDcolor = 0;
  }
  if(LEDNum == 4) {
    RLEDcolor = 0;
    GLEDcolor = 0;
    BLEDcolor = 255;
  }
  Rcurrentcolor = RLEDcolor;
  Gcurrentcolor = GLEDcolor;
  Bcurrentcolor = BLEDcolor;
}

void changeMODE() {
  currentMode++;
  if(currentMode>=3) {
    currentMode = 0;
  }
  if(currentMode == 1) {
    blinkTimer = 0;
    blinkOn = true;
  }
  if (currentMode == 2) {
    FadeDirection = 1;
  }
}

void updateLEDcolor() {
  if(currentMode == 0) {
    Rcurrentcolor = RLEDcolor;
    Gcurrentcolor = GLEDcolor;
    Bcurrentcolor = BLEDcolor;
  }else if(currentMode == 1) {
    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval) {
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }
    if(blinkOn) {
      Rcurrentcolor = RLEDcolor;
      Gcurrentcolor = GLEDcolor;
      Bcurrentcolor = BLEDcolor;
    }else {
      Rcurrentcolor = 255;
      Gcurrentcolor = 255;
      Bcurrentcolor = 255;
    }
  }else if (currentMode == 2) {
    // 漸變模式
    bool reverse = false;

    if (RLEDcolor == 0) {
      Rcurrentcolor += FadeDirection * fadeAmount;
      if (Rcurrentcolor <= 0 || Rcurrentcolor >= 255) reverse = true;
    }
    if (GLEDcolor == 0) {
      Gcurrentcolor += FadeDirection * fadeAmount;
      if (Gcurrentcolor <= 0 || Gcurrentcolor >= 255) reverse = true;
    }
    if (BLEDcolor == 0) {
      Bcurrentcolor += FadeDirection * fadeAmount;
      if (Bcurrentcolor <= 0 || Bcurrentcolor >= 255) reverse = true;
    }

    if (reverse) FadeDirection = -FadeDirection;

    Rcurrentcolor = constrain(Rcurrentcolor, 0, 255);
    Gcurrentcolor = constrain(Gcurrentcolor, 0, 255);
    Bcurrentcolor = constrain(Bcurrentcolor, 0, 255);

    delay(10);
  }
}
