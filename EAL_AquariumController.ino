



#include <LiquidCrystal.h>
#include <Servo.h>
#include <EEPROM.h>
#include <EEWrap.h>
#include <Wire.h>
#include <TimeLib.h>
#include <Time.h>
#include <DigitalTime.h>
#include <DS3232RTC.h>
#include <SimpleTimer.h> //events



#include <StandardCplusplus.h>
#include <vector>
using namespace std;

//**EAL-Includes
#include <AnalogSwitch.h>
#include <RODoser.h>
#include <LCDMenuController.h>
#include <SerialExt.h>
#include <RTCExt.h>
#include <LCDMenu.h>
using namespace Utils;
using namespace Controllers;

//**LCD-BEGIN**

// LCD Digital Pins: 0, 1, 2, 3, 11, 12, 13
// LCD Analog Pins: A1, A2, A3, A4, A5
// LCD Analog to Digital Pins: 15, 16, 17, 18, 19

// pin listing (on LCD)
short _feederPin = 0;
short _feeder2Pin = 1;
short _doserPin = 3;
short _floatSwitchPin = A3;

//LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
//LiquidCrystal _lcd(8, 13, 9, 4, 5, 6, 7);

bool _timersEnabled = true;

SimpleTimer _menuTimeoutTimer;
SimpleTimer _selectPressTimer;

LCDMenuController _lcdMenuController;
//**LCD-END**

//**Doser-BEGIN**
//AnalogSwitch _floatSwitch(_floatSwitchPin);
//Servo _servo;
//RODoser _doser;
//**Doser-END**

void setup() {

	Serial.begin(9600);
	while (Serial.available() == 0 && millis() < 2000); // wait until Arduino Serial Monitor opens

	RTCExt::Init();

	Serial.println("a");
	//_doser = RODoser(_servo, _doserPin, 2, 22000, _floatSwitch);

	_selectPressTimer.setInterval(1000, IsSelectPressed);
	_menuTimeoutTimer.setTimeout(20000, MenuTimeout);

	//SerialExt::Debug(RTCExt::IsRTCTimeSet());
	//RTCExt::SetRTCTime(9, 42, 0, 8, 4, 2016);
	if (!RTCExt::IsRTCTimeSet())
		_lcdMenuController.SelectMainMenu();

}

void loop() {
	if (_timersEnabled){
		//_timer.run();
		_selectPressTimer.run();
	}
}


void IsSelectPressed()
{

	int key = _lcdMenuController.GetKey();
	//SerialExt::Debug("keys:", key);

	if (key == 4){
		_timersEnabled = false; //disable
		_menuTimeoutTimer.run();
		_lcdMenuController.SelectMainMenu();
		_timersEnabled = true; //enable


	}

	_lcdMenuController.Scroll();
}


void MenuTimeout(){
	SerialExt::Debug("Menu Timeout");
	_lcdMenuController.ExitMainMenu();
}

void FeedFish(){
	//long countDown = RTCExt::NextFeedInfo.CountDown;
	long nextRun = RTCExt::NextFeedInfo.NextRun;

	RTCExt::NextFeedInfo.LastRun = RTCExt::GetRTCTime();

}




