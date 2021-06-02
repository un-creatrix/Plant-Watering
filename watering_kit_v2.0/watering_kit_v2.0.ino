#include <Wire.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);    // I2C
#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 RTC;

int pump = 4; // Pin for Water Pump

// Declaration of Plants [Pump Port, Sensor Port, Time Watered, Moisture Reqd]
//char json[] = "{1:["pump":6, "Sensor":"A0", "Watered":0, "MoReqd":.8], 2:["pump":8, "Sensor":"A1", "Watered":0, "MoReqd":.8], 3:["pump":9, "Sensor":"A2", "Watered":0, "MoReqd":.8], 4:["pump":10, "Sensor":"A3", "Watered":0, "MoReqd":.8],}";

void setup() {
	Serial.begin(9600);
	while(!Serial) continue;
	Serial.println("Welcome to Plant Hub! Software v2.0.2");
	pinMode(pump, OUTPUT);
	digitalWrite(pump, HIGH);
	delay(200);
	digitalWrite(pump,LOW);




}
void loop() {

}