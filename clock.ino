#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int TIMESTEP = 1000; //delay between each update
const byte SEC_IN_MIN = 60;
const byte MIN_IN_HOUR = 60;
const byte HOUR_IN_DAY = 24;

byte currentSecs = 0;
byte currentMins = 0;
byte currentHours = 0;

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
}

void lcdClear() {
	lcd.clear();
	lcd.setCursor(0,0);
}

void setup()
{
	lcd.begin(16, 2);
	lcd.print("Setup Func");
}

void loop()
{
	UpdateTime();
	lcdClear();
	String s = String(currentHours) + String(':') + String(currentMins) + String(':') + String(currentSecs);
	lcd.print(s);
  delay(TIMESTEP);
}