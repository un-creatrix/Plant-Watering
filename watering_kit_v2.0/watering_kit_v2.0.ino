#include <Wire.h>
#include "U8glib.h"
#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 RTC;
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// Defines OLED Panel
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

int pump = 4; // Pin for Water Pump
// All for RTC
static unsigned long currentMillis_send = 0;
static unsigned long  Lasttime_send = 0;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat",};
unsigned long nowtime;
unsigned long endtime;
unsigned long nowtimeNext;
unsigned long nowtime1;
unsigned long endtime1;
unsigned long nowtimeNext1;
unsigned long nowtime2;
unsigned long endtime2;
unsigned long nowtimeNext2;
unsigned long nowtime3;
unsigned long endtime3;
unsigned long nowtimeNext3;

// Declaration of Plants [Pump Port, Sensor Port, Time Watered, Moisture Reqd]
int PumpPort [] = {6, 8, 9, 10};
word SensPort [] = {"A0", "A1", "A2", "A3"};
int TimeWtr  [] = {0, 0, 0, 0};
float MoistRqd [] = {.8, .8, .8, .8};

void setup() {
	display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
	Serial.begin(9600);
	display.clearDisplay();
	display.display();
	//while(!Serial) continue;
	Serial.println("Welcome to Plant Hub! Software v2.0.2");
	pinMode(pump, OUTPUT);
	digitalWrite(pump, HIGH);
	delay(200);
	digitalWrite(pump,LOW);
	display.clearDisplay();
	display.display();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Pump Test - Passed");
	display.display();
	// Relay loop through test
	Serial.print("Testing Plant Port => ");
	display.print("Testing Plant Ports  > ");
	for (int p = 0; PumpPort[p] != NULL; p++) {
		if (p != 0 ) {Serial.print(", "); display.print(", ");};
		pinMode(PumpPort[p], OUTPUT);
		digitalWrite(PumpPort[p], HIGH);
		delay(200);
		digitalWrite(PumpPort[p],LOW);
		Serial.print(p);
		display.print(p+1);
		display.display();
	}
	for (int p = 0; SensPort[p] != NULL; p++) {

	}


	Serial.print("\n");
}
void loop() {

}