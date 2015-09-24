#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte DAY_BTN_PIN = 6;
const byte HOUR_BTN_PIN = 7;
const byte MIN_BTN_PIN = 8;
const byte SEC_BTN_PIN = 9;

unsigned long previousTimestep = 0;
unsigned long previousLCDTimestep = 0;

const int LCD_TIMESTEP = 10;
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

void OnSecond () {
  currentSecs++;
  UpdateTime();
}

void lcdClear() {
  lcd.clear();
  lcd.setCursor(0,0);
}

void PrintToLCD() {
  lcdClear();
  lcd.print(dayToString[currentDayIndex]);
  lcd.setCursor(0,1);
  String s = String(currentHours) + String(':') + String(currentMins) + String(':') + String(currentSecs);
  lcd.print(s);
}

bool prevDay, prevMin, prevHour, prevSec;

void HandleButtons() {
  bool ChangeDay = digitalRead(DAY_BTN_PIN);
  bool ChangeMin = digitalRead(MIN_BTN_PIN);
  bool ChangeHour = digitalRead(HOUR_BTN_PIN);
  bool ChangeSec = digitalRead(SEC_BTN_PIN);

  if (ChangeDay && !prevDay) {
    currentDayIndex++;
  }

  if (ChangeHour && !prevHour) {
    currentHours++;
  }

  if (ChangeMin && !prevMin) {
    currentMins++;
  }

  if (ChangeSec && !prevSec) {
    currentSecs++;
  }

  UpdateTime();

  prevDay = ChangeDay;
  prevHour = ChangeHour;
  prevMin = ChangeMin;
  prevSec = ChangeSec;
}

void setup()
{
  pinMode(DAY_BTN_PIN,  INPUT);
  pinMode(HOUR_BTN_PIN, INPUT);
  pinMode(MIN_BTN_PIN,  INPUT);
  pinMode(SEC_BTN_PIN,  INPUT);

  lcd.begin(16, 2);
  lcd.print("Setup Func");
}

unsigned long currentMillis = 0;

void loop()
{
  HandleButtons();

  currentMillis = millis();
  if (currentMillis - previousTimestep > TIMESTEP) {
    previousTimestep = currentMillis;
    OnSecond();
  }

  if (currentMillis - previousLCDTimestep > TIMESTEP) {
    previousLCDTimestep = currentMillis;
    PrintToLCD();
  }
}

