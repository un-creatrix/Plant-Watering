#include <Wire.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);    // I2C
#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 RTC;

int pump = 4; // Pin for Water Pump

// Declaration of Plants [Pump Port, Sensor Port, Time Watered, Moisture Reqd]
int PumpPort [] = {6, 8, 9, 10};
word SensPort [] = {"A0", "A1", "A2", "A3"};
int TimeWtr  [] = {0, 0, 0, 0};
float MoistRqd [] = {.8, .8, .8, .8};

void setup() {
	Serial.begin(9600);
	//while(!Serial) continue;
	Serial.println("Welcome to Plant Hub! Software v2.0.2");
	pinMode(pump, OUTPUT);
	digitalWrite(pump, HIGH);
	delay(200);
	digitalWrite(pump,LOW);
	// Relay loop through test
	Serial.print("Testing Plant Port => ");
	for (int p = 0; PumpPort[p] != NULL; p++) {
		if (p != 0 ) {Serial.print(", ");};
		pinMode(PumpPort[p], OUTPUT);
		digitalWrite(PumpPort[p], HIGH);
		delay(200);
		digitalWrite(PumpPort[p],LOW);
		Serial.print(p);
	}
	for (int p = 0; SensPort[p] != NULL; p++) {

	}


	Serial.print("\n");
}
void loop() {

}