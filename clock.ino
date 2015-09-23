#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte DAY_BTN_PIN = 6;
const byte HOUR_BTN_PIN = 7;
const byte MIN_BTN_PIN = 8;
const byte SEC_BTN_PIN = 9;

const int TIMESTEP = 1000; //delay between each update
const byte SEC_IN_MIN = 60;
const byte MIN_IN_HOUR = 60;
const byte HOUR_IN_DAY = 24;
const byte DAYS_IN_WEEK = 7; //Maximum Day Index + 1

const char dayToString[DAYS_IN_WEEK][10] = {
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

byte currentSecs = 55;
byte currentMins = 59;
byte currentHours = 23;
byte currentDayIndex = 5;

void UpdateTime () {
  currentSecs++;

  if (currentSecs >= SEC_IN_MIN) {
    currentSecs = 0;
    currentMins++;
  }

  if (currentMins >= MIN_IN_HOUR) {
    currentMins = 0;
    currentHours++;
  }

  if (currentHours >= HOUR_IN_DAY) {
    currentHours = 0;
    currentDayIndex++;
  }

  if (currentDayIndex >= DAYS_IN_WEEK) {
    currentDayIndex = 0;
  }
}

void lcdClear() {
  lcd.clear();
  lcd.setCursor(0,0);
}

void setup()
{
  pinMode(DAY_BTN_PIN,  INPUT);
  PinMode(HOUR_BTN_PIN, INPUT);
  PinMode(MIN_BTN_PIN,  INPUT);
  PinMode(SEC_BTN_PIN,  INPUT);

  lcd.begin(16, 2);
  lcd.print("Setup Func");
}

void loop()
{
  UpdateTime();
  //Update Diplay
  lcdClear();
  lcd.print(dayToString[currentDayIndex]);
  lcd.setCursor(0,1);
  String s = String(currentHours) + String(':') + String(currentMins) + String(':') + String(currentSecs);
  lcd.print(s);
  //Delay for timing
  delay(TIMESTEP);
}

