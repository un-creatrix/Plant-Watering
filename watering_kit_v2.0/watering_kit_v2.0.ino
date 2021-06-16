#include "Wire.h"				// Introduces I2C support
#include "RTClib.h"				// Real Time Clock
#include <Adafruit_GFX.h>		// OLED GFX Library
#include <Adafruit_SH1106.h>	// Modified Library for OLED to Support SH1106
#include "WatchDog.h"			// Library to simplify working with watchdog inside of script

// Defines OLED Panel
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

// All Graphics
const unsigned char Bloomed [] PROGMEM = {
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x02, 0xb0, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x04, 0x37, 0xf1, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x07, 0xc9, 0x06, 0xe8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x1f, 0x0a, 0xb4, 0x00, 0x00, 
	0x00, 0x05, 0xd2, 0x4e, 0x04, 0x1f, 0x00, 0x00, 0x00, 0x05, 0x7b, 0xff, 0xd4, 0x67, 0x00, 0x00, 
	0x00, 0x03, 0x4a, 0x00, 0x35, 0xbe, 0x00, 0x00, 0x00, 0x02, 0xa0, 0x52, 0x56, 0xd4, 0x80, 0x00, 
	0x00, 0x01, 0xc0, 0x51, 0xcd, 0x08, 0x80, 0x00, 0x00, 0xc3, 0x6c, 0xff, 0xb2, 0x70, 0x80, 0x00, 
	0x01, 0x02, 0x66, 0x00, 0x3f, 0xb1, 0x00, 0x00, 0x02, 0x00, 0x58, 0x78, 0x80, 0x71, 0x30, 0x00, 
	0x04, 0x31, 0x13, 0x82, 0x3f, 0xe3, 0x81, 0xc0, 0x04, 0x70, 0x34, 0x00, 0x03, 0x3a, 0x04, 0x20, 
	0x02, 0x86, 0x58, 0x80, 0x04, 0x54, 0x00, 0x10, 0x0d, 0xcd, 0x9e, 0x00, 0x00, 0x10, 0x00, 0x50, 
	0x10, 0x31, 0x70, 0x80, 0x00, 0x00, 0xd8, 0x70, 0x20, 0x08, 0xcc, 0xe8, 0x00, 0x22, 0x60, 0xd0, 
	0x40, 0x0c, 0x01, 0x80, 0x00, 0x23, 0xa0, 0x10, 0x80, 0x0b, 0xff, 0xe0, 0x01, 0xcc, 0x00, 0xa0, 
	0x84, 0x08, 0x80, 0x70, 0x43, 0xf0, 0x00, 0x40, 0x8e, 0x00, 0x34, 0x18, 0x20, 0x40, 0x08, 0x80, 
	0x71, 0x04, 0x40, 0x08, 0x20, 0x67, 0x87, 0x00, 0x04, 0x00, 0x40, 0x04, 0x7c, 0x70, 0x70, 0x00, 
	0x03, 0x04, 0xb0, 0x15, 0xa3, 0x80, 0x98, 0x00, 0x00, 0x98, 0x30, 0x7f, 0xf2, 0x3f, 0x04, 0x00, 
	0x00, 0x67, 0xe0, 0x26, 0x68, 0x0f, 0x82, 0x00, 0x00, 0x00, 0x11, 0xc7, 0x64, 0x0c, 0x02, 0x00, 
	0x00, 0x00, 0x08, 0x05, 0x92, 0x80, 0x3a, 0x00, 0x00, 0x00, 0x06, 0x07, 0x85, 0x00, 0x46, 0x00, 
	0x00, 0x00, 0x01, 0x8c, 0x39, 0x18, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xe2, 0x40, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00//	// 60 X 35
};
const unsigned char Bloom [] PROGMEM = {
	0x00, 0x60, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x04, 0xf2, 0x00, 0x00, 0x03, 0x4c, 0x07, 0x00, 
	0x0b, 0x0b, 0xf8, 0x80, 0x0c, 0x3e, 0x60, 0x00, 0x7d, 0xef, 0x96, 0x00, 0x68, 0x6a, 0x48, 0x80, 
	0x55, 0x55, 0x2f, 0x80, 0x46, 0x49, 0x5b, 0x30, 0x53, 0xd2, 0xaf, 0xc8, 0x29, 0x08, 0xaa, 0x24, 
	0x30, 0xe1, 0x2a, 0x24, 0x19, 0x32, 0x2a, 0x28, 0x14, 0x59, 0xe0, 0x58, 0x01, 0xa7, 0x01, 0x10, 
	0x0e, 0x70, 0xc1, 0x60, 0x08, 0xcf, 0xe3, 0x20, 0x0c, 0xc7, 0x18, 0xc0, 0x01, 0x16, 0x28, 0xc0, 
	0x10, 0x00, 0x55, 0xc0, 0x10, 0x00, 0x8d, 0x40, 0x10, 0x01, 0x38, 0x40, 0x18, 0x00, 0x33, 0xc0, 
	0x18, 0x00, 0x33, 0x40, 0x04, 0x00, 0x5b, 0xc0, 0x10, 0x00, 0xd0, 0xc0, 0x12, 0x80, 0xf4, 0xc0, 
	0x12, 0x00, 0x04, 0xc0, 0x15, 0x00, 0x08, 0xc0, 0x0b, 0xc0, 0x95, 0x00, 0x04, 0xa0, 0x34, 0x80, 
	0x02, 0x20, 0x49, 0x00, 0x01, 0xc3, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00	// 30 X 35
};
const unsigned char Bud [] PROGMEM = {
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x40, 0x0a, 0x00, 0x00, 0xa0, 0x0a, 0x00, 
	0x00, 0x80, 0x06, 0x00, 0x01, 0x5f, 0xe6, 0x10, 0x01, 0x77, 0xd5, 0x30, 0x01, 0x7b, 0xad, 0x30, 
	0x02, 0x4e, 0x7d, 0x38, 0x32, 0x6f, 0x65, 0x28, 0x53, 0x2c, 0x05, 0x28, 0x55, 0xa8, 0x33, 0xa8, 
	0x65, 0x33, 0x22, 0xa8, 0x65, 0x33, 0x31, 0xa8, 0x6a, 0x6a, 0x82, 0xe8, 0x5e, 0x22, 0x80, 0x68, 
	0x54, 0x22, 0xd2, 0x68, 0x5a, 0x14, 0x50, 0x28, 0x58, 0x2c, 0xa2, 0x28, 0x56, 0x6c, 0xa2, 0x28, 
	0x50, 0x68, 0xd2, 0x28, 0x93, 0x1c, 0x90, 0x28, 0x90, 0x10, 0x09, 0x78, 0xb1, 0x28, 0x09, 0x48, 
	0xb9, 0x20, 0x04, 0x48, 0x89, 0x44, 0x14, 0x50, 0x4b, 0x40, 0x94, 0xd0, 0x54, 0x44, 0x9c, 0x90, 
	0x26, 0x40, 0x85, 0xa0, 0x17, 0x44, 0x85, 0x20, 0x09, 0xc4, 0x86, 0x40, 0x07, 0x44, 0x4d, 0x80, 
	0x01, 0xa8, 0x8e, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00		// 30 X 35
};
const unsigned char Watering [] PROGMEM = {
	0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x00, 0x6f, 0x01, 0xe0, 0x00, 0x01, 
	0xff, 0xc0, 0x78, 0x00, 0x03, 0x80, 0xe0, 0x1c, 0x00, 0x07, 0x00, 0x37, 0xde, 0x00, 0x0c, 0x00, 
	0x1c, 0x6b, 0x00, 0x18, 0x00, 0x0c, 0x29, 0x80, 0x13, 0x83, 0xcd, 0x29, 0x80, 0x3f, 0xf7, 0xe5, 
	0xa8, 0xc0, 0x38, 0x3c, 0x36, 0x18, 0xc0, 0x60, 0x18, 0x97, 0xf0, 0xc0, 0x60, 0x0d, 0x97, 0xc7, 
	0xc0, 0x43, 0x8d, 0xe4, 0x7f, 0xe0, 0xc6, 0xc4, 0xcd, 0xf8, 0xe0, 0xc8, 0x26, 0x3b, 0x80, 0x40, 
	0xd9, 0x27, 0xf6, 0x00, 0x60, 0xd9, 0xa4, 0x9c, 0x07, 0xe0, 0xd9, 0xec, 0x38, 0x3f, 0xe0, 0xc8, 
	0x10, 0x70, 0xf0, 0x60, 0xcc, 0x38, 0xe1, 0xc0, 0x60, 0xe7, 0xe1, 0x83, 0x00, 0x60, 0xf0, 0x07, 
	0x06, 0x03, 0xc0, 0x3f, 0xfe, 0x0c, 0x0f, 0xc0, 0x7f, 0xf8, 0x18, 0x3c, 0xc0, 0x60, 0x00, 0x30, 
	0x70, 0x80, 0x30, 0x00, 0xe1, 0xc1, 0x80, 0x3c, 0x07, 0x83, 0x83, 0x00, 0x1f, 0xfe, 0x07, 0x03, 
	0x00, 0x0f, 0xf0, 0x0e, 0x04, 0x00, 0x06, 0x00, 0x1c, 0x18, 0x00, 0x03, 0xc0, 0x78, 0x38, 0x00, 
	0x00, 0xff, 0xe1, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x04, 0x7c, 0x00, 0x00	// 35 X 35
};

// Defines for Physical Pins
int pump = 4; 			// Pin for Water Pump
int sideButton = 12;	// Side Menu Control Button

// All for RTC
RTC_DS1307 RTC;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat",};

//Sensor Calibration Defaults for Fixed Humidity
int Hum100 = 300;
int Hum0   = 591;
float roundingMoisture = 5;

// Declaration of Plants [Pump Port, Sensor Port, Time Watered, Moisture Reqd]
const char *Plant [] 	= {"Peppermint", "Peppermint", "None", "None", NULL}; // Plant Name // None Removes port from display loop
const int PumpPort [] 	= { 6 ,  8,  9,  10, NULL}; // Pump Port Plant is on
const byte SensPort [] 	= { A0,  A1,  A2,  A3, NULL}; // A port selection for plants
int moisture []         = { 0,  0,  0,  0, NULL};
bool PlantWtr [] 		= { false, false,  false, false, NULL}; // Does the plant need water
int TimeWtr  [] 		= { 0,  0,  0,  0};       // Amount of time plant has been watered for
const int MoistRqd [] 	= { 80,  80,  0,  0};	      // Moisture Required by Plant // 0 Acts as no watering place holder

void SensorInit(bool init = false) {								// Initializing and displaying sensor values
	if (init) {display.clearDisplay();};
	display.setCursor(0, 0);
	// Sensor loop through test
	if (init) {Serial.print("Testing Plant Sensor => ");};
	display.setTextSize(2);
	display.println("Sensors");
	display.setTextSize(1);
	display.println("Port - % - Volt Ref");
	display.display();
	for (int p = 0; SensPort[p] != NULL ; p++) {
		if (p != 0 ) {if (init) {Serial.print(", ");delay(100);}; display.print("\n");};
		if (init) {Serial.print(SensPort[p]);};
		display.print(SensPort[p]);
		int reading = analogRead(SensPort[p]);
		int reading_mapped =map(reading,Hum0,Hum100,0,100);
		delay(10);
		if (reading_mapped > 100 or reading_mapped < 0) {
			display.setTextColor(BLACK, WHITE);
		}
		if (init) {Serial.print("-");};
		display.print(" - ");
		if (init) {Serial.print(reading_mapped);};
		display.print(reading_mapped);
		if (init) {Serial.print("-");}
		display.print(" - ");
		if (init) {Serial.print(reading);};
		display.print(reading);
		display.display();
		display.setTextColor(WHITE, BLACK);
	}
	if (init) {Serial.print("\n");};
}
void watering(void) {												// watering script that runs in every base routine to ensure safe watering
	bool flag = false;
	for (int i = 0; SensPort[i] != NULL; i ++) {
		int reading = analogRead(SensPort[i]);
		moisture[i] = map(reading,Hum0,Hum100,0,100);
		if (moisture[i] < 0) {moisture[i] = 0;} // Forces Min to 0 for Reading
		if (moisture[i] > 100) {moisture[i] = 100;} // Forces Max to 100 for Reading
		if (MoistRqd[i] != 0) {
			if (moisture[i] < MoistRqd[i]) {PlantWtr[i] = true;} else {PlantWtr[i] = false;}
		}
	}
	for (int i = 0; SensPort[i] != NULL; i ++) {
		if (PlantWtr[i]) {digitalWrite(PumpPort[i], HIGH);} else {digitalWrite(PumpPort[i], LOW);} // Enables Pump Port to plant needing water
		if (PlantWtr[i]) {flag = true;}				// Sets flag to enable pump once ready to water
		PlantWtr[i] = false;
	}
	if (flag) {
		WatchDog::init(StopAction, 500);
		digitalWrite(pump, HIGH);
	} else {
		digitalWrite(pump, LOW);
		WatchDog::stop();
	}
}
String issuedCMD;
void SerialCMD(String issuedCMD = "None") {	// Reads Serial Commands Issued
	if (issuedCMD != "None" and issuedCMD != "HELP") {
		StopAction();
	}
	if (issuedCMD == "HELP") {			// 'HELP' Command Typed
	Serial.println("List of commands that can be issued are:");
	Serial.println("RTC-status				- Real Time Clock, Gets Status of Clock");
	Serial.println("RTC-read				- Real Time Clock, Reads Time and Date");
	Serial.println("RTC-config				- Real Time Clock, Starts Config Process");
	Serial.println("RTC-reset				- Real Time Clock, Reset");
	Serial.println("SENSOR-init				- Moisture Sensor, Init");
	Serial.println("SENSOR-high				- Moisture Sensor, Sets 100% Moisture Value");
	Serial.println("SENSOR-low				- Moisture Sensor, Sets 0%	Moisture Value");
	Serial.println("RELAY-test				- Relay, Test Mode");
	Serial.println("LCD-test				- OLED Display, Test Patterns");
	} else if (issuedCMD == "RTC-status") {	// 'RTC-read' Command Typed
	} else if (issuedCMD == "RTC-config") {	// 'RTC-config' Command Typed
		Serial.println("Config for Real Time Clock");
		Serial.println("Year:");
		Serial.println("Month:");
		Serial.println("Day:");
		Serial.println("24 Hour:");
		Serial.println("Minute:");
	} else if (issuedCMD == "RTC-reset") {	// 'RTC-reset' Command Typed
	} else if (issuedCMD == "None") {	// No Command Issued
	} else {
		Serial.print("\'");
		Serial.print(issuedCMD);
		Serial.println("\' - is not a command, Type HELP for list of commands");
	}
}
void setup() {
	display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
	WatchDog::init(StopAction, 4000); // Watchdog startup and defining script (function to run on failure to feed, feed rate required)
	Serial.begin(9600);
	display.clearDisplay();
	display.fillRect(0, 0, 128, 64, WHITE);
	display.drawBitmap(47, 15, Watering, 35, 35, BLACK);
	display.display();
	delay(500);
	//while(!Serial) continue;
	Serial.println("Welcome to Plant Hub! Software v2.0.2");
	display.clearDisplay();
	display.display();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.setTextSize(2);
	display.println("Pump Link");
	pinMode(pump, OUTPUT);
	digitalWrite(pump, HIGH);
	delay(50);
	digitalWrite(pump,LOW);
	display.setTextSize(3);
	display.println("Passed");
	display.display();
	delay(500); // Delay to Bleed Pressure Down
	display.clearDisplay();
	display.display();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.setTextSize(2);
	display.println("Time Clock");
	display.setTextSize(1);
	if (! RTC.begin()) {
	    display.println("Failed Connection");
	} else {
		display.println("I2C - Connection");
	}
	if (! RTC.isrunning()) {
		display.println("Time Not Set on Clock");
	} else {
		display.println("Date 00/00/0000");
		display.println("Time   00:00:00");
	}
	display.print("+ WatchDog - ");
	display.println(WatchDog::getPeriod());
	display.display();
	delay(750); // Allows user to read data
	display.clearDisplay();
	display.setCursor(0, 0);
	// Relay loop through test
	display.setTextSize(2);
	display.println("Ports");
	display.display();
	display.setTextSize(1);
	for (int p = 0; PumpPort[p] != NULL; p++) {
		pinMode(PumpPort[p], OUTPUT);
		digitalWrite(PumpPort[p], HIGH);
		delay(50);
		display.print(p+1);
		display.print(" - ");
		display.println(Plant[p]);
		display.display();
		digitalWrite(PumpPort[p],LOW);
	}
	delay(500);
	SensorInit(true); // Function for Initializing Sensors
	display.println();
	display.print("+ WatchDog - ");
	display.println(WatchDog::getPeriod());
	WatchDog::stop();
	display.display();
	delay(750);
}

void loop() {
	for (int c = 0; c <= 1000; c = c+10) {
		watering(); // Calls on Script to manage watering events
		display.fillRect(0, 0, 128, 61, BLACK);
		display.setTextColor(WHITE, BLACK);
		display.setCursor(0,0);
		display.setTextSize(2);
		display.println("Water Hub");
		display.setTextSize(1);
		display.println();
		display.println("Date 00/00/0000");
		display.println("Time   00:00:00");
		display.print("WatchDog - ");
		display.println(WatchDog::status() ? ("Watch") : ("Asleep"));
		display.display();
		// Reload status bar
		display.fillRect(0, 61, 128, 3, BLACK);
		display.fillRect(0, 61, 64, 3, WHITE);
		display.fillRect(0, 61, map(c,0,1000,0,64), 3, BLACK);
		display.fillRect(64, 61, map(c,0,1000,64,0), 3, WHITE);
		display.display();
	}
	for (int plant = 0; Plant[plant] != NULL; plant++) { //Loops through each plant on display screen
		if (Plant[plant] != "None") {
			display.clearDisplay();
			display.setTextColor(WHITE, BLACK);
			display.setCursor(0,0);
			display.setTextSize(2);
			display.println(Plant[plant]);
			display.drawBitmap(5, 20, Bud, 30, 35, WHITE);
			for (int c = 0; c <= 1000; c = c+10) {
				watering(); // Calls on Script to manage watering events
				if(Serial.available()){ SerialCMD(Serial.readStringUntil('\n')); } // Runs Function when serial is connected
				display.fillRect(43, 20, 85, 40, BLACK);
				//Plant Number
				display.setCursor(43,20);
				display.setTextSize(1);
				display.print("Plant - ");
				display.print(plant+1);
				display.print(" of ");
				display.println(4);
				//Plant Moisture
				display.setCursor(43,30);
				display.setTextSize(1);
				display.print("Moisture  ");
				int moistRound = moisture[plant]/roundingMoisture;
				moistRound = moistRound*roundingMoisture;
				if (moistRound < 10) {display.print("  ");} else if (moistRound < 100 and moistRound >= 10) {display.print(" ");}
				display.print(moistRound);
				display.print("%");
				//Plant Required Moisture
				display.setCursor(43,40);
				display.setTextSize(1);
				display.print("Required  ");
				if (MoistRqd[plant] < 10) {display.print("  ");} else if (MoistRqd[plant] < 100 and MoistRqd[plant] >= 10) {display.print(" ");}
				display.print(MoistRqd[plant]);
				display.print("%");
				//Watering Time
				display.setCursor(43,50);
				display.setTextSize(1);
				display.print("Watrd ");
				display.print("00:00:00");
				// Reload status bar
				display.fillRect(0, 61, 128, 3, BLACK);
				display.fillRect(0, 61, 64, 3, WHITE);
				display.fillRect(0, 61, map(c,0,1000,0,64), 3, BLACK);
				display.fillRect(64, 61, map(c,0,1000,64,0), 3, WHITE);
				display.display();
			}
		}
	}
}
void StopAction(void) { // Function to be called in event of hang or system failure
	WatchDog::stop();
	Serial.println("!!! - Stop Watering Issued - !!!");
	digitalWrite(pump,LOW);
	for (int p = 0; PumpPort[p] != NULL; p++) {
		digitalWrite(PumpPort[p],LOW);
	}     
}