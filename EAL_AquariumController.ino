

#define SERIAL_BUFFER_SIZE 256

//#include <LiquidCrystal.h>
//#include <Servo.h>
//#include <EEPROM.h>
//#include <Wire.h>
//#include <TimeLib.h>
//#include <Time.h>
//#include <DS3232RTC.h>
//#include <MemoryFree.h>

#include <SimpleTimer.h> //events

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

//**EAL-Includes
#include <SerialExt.h>
//#include <DigitalTime.h>
//#include <MemoryExt.h>
#include <RTCExt.h>
//#include <AnalogSwitch.h>
//#include <RODoser.h>
//#include <LCDMenu.h>
//#include <LCDMenuController.h>


using namespace Utils;

//using namespace Models;
//using namespace Time;


//**LCD-BEGIN**

// LCD Digital Pins: 0, 1, 2, 3, 11, 12, 13
// LCD Analog Pins: A1, A2, A3, A4, A5
// LCD Analog to Digital Pins: 15, 16, 17, 18, 19

// pin listing (on LCD)
short _feederPin = 0;
short _feeder2Pin = 1;
short _doserPin = 3;
short _floatSwitchPin = A3;
//struct LocalVars{
//int16_e _feederPin = 0;
//int16_e _feeder2Pin = 1;
//int16_e _doserPin = 3;
//int16_e _floatSwitchPin = A3;
//};

//LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
//LiquidCrystal _lcd(8, 13, 9, 4, 5, 6, 7);

bool _timersEnabled = true;

SimpleTimer _menuTimeoutTimer;
SimpleTimer _selectPressTimer;

//LCDMenuController _lcdMenuController;
//**LCD-END**

//**Doser-BEGIN**
//AnalogSwitch _floatSwitch(_floatSwitchPin);
//Servo _servo;
//RODoser _doser;
//**Doser-END**


void setup() {

	Serial.begin(115200);
	while (!Serial);
	while (Serial.available() == 0 && millis() < 2000); // wait until Arduino Serial Monitor opens

	Serial.print(F("Buffer Size: "));
	Serial.println(SERIAL_BUFFER_SIZE);
	
	RTCExt::Init();
	//_lcdMenuController = LCDMenuController();
	
	TestLoadNRMem();

	return;

	//Serial.println(F("a"));
	//_doser = RODoser(_servo, _doserPin, 2, 22000, _floatSwitch);


	//_selectPressTimer.setInterval(500, IsSelectPressed);
	//_menuTimeoutTimer.setTimeout(200000, MenuTimeout);

	//SerialExt::Debug(RTCExt::IsRTCTimeSet());
	//RTCExt::SetRTCTime(9, 42, 0, 8, 4, 2016);
	//if (!RTCExt::IsRTCTimeSet())
	//	_lcdMenuController.SelectMainMenu();

}
static NextRunMemory _doseInfo;
static NextRunMemory _feedInfo;
void TestLoadNRMem(){
	SerialExt::Debug("--Load_FeedInfo--");
	int accType = static_cast<int>(AccessoryType::Feeder);
	_feedInfo.AccType = accType;
	_feedInfo = RTCExt::GetNextRunMem(_feedInfo);

	SerialExt::Debug("--Load_DoseInfo--");
	int accType2 = static_cast<int>(AccessoryType::DryDoser);
	_doseInfo.AccType = accType2;
	_doseInfo = RTCExt::GetNextRunMem(_doseInfo);
}
void TestNRMem(){

	SerialExt::Debug("--FeedInfo--");
	
	int accType = static_cast<int>(AccessoryType::Feeder);
	
	_feedInfo.AccType = accType;
	_feedInfo.CountDown = 1000L;
	_feedInfo.LastRun = 2000L;
	_feedInfo.NextRun = 3000L;
	_feedInfo.RunEvery = 4000L;
	_feedInfo.ShakesOrTurns = (short)5;
	
	_feedInfo = RTCExt::SaveNextRunMem(_feedInfo);
	_feedInfo = RTCExt::GetNextRunMem(_feedInfo);

	SerialExt::Debug("--DoseInfo--");

	int accType2 = static_cast<int>(AccessoryType::DryDoser);

	_doseInfo.AccType = accType2;
	_doseInfo.CountDown = 6000L;
	_doseInfo.LastRun = 7000L;
	_doseInfo.NextRun = 8000L;
	_doseInfo.RunEvery = 9000L;
	_doseInfo.ShakesOrTurns = (short)8;

	_doseInfo = RTCExt::SaveNextRunMem(_doseInfo);
	_doseInfo = RTCExt::GetNextRunMem(_doseInfo);

	SerialExt::Debug("--FeedInfo Update--");
	_feedInfo.CountDown = 1500L;
	_feedInfo = RTCExt::SaveNextRunMem(_feedInfo);
	_feedInfo = RTCExt::GetNextRunMem(_feedInfo);

	SerialExt::Debug("--DoseInfo Update--");
	_doseInfo.CountDown = 6500L;
	_doseInfo = RTCExt::SaveNextRunMem(_doseInfo);
	_doseInfo = RTCExt::GetNextRunMem(_doseInfo);

}

void loop() {
	//if (_timersEnabled){
	//	//_timer.run();
	//	_selectPressTimer.run();
	//}
}


void IsSelectPressed()
{

	//int key = _lcdMenuController.GetKey();
	//SerialExt::Debug("key_isp", key);

	//if (key == 4){
	//	_timersEnabled = false; //disable
	//	_menuTimeoutTimer.run();
	//	_lcdMenuController.SelectMainMenu();
	//	_timersEnabled = true; //enable


	//}

	//_lcdMenuController.Scroll();
}


void MenuTimeout(){
	/*SerialExt::Debug("Menu Timeout");
	_lcdMenuController.ExitMainMenu();*/
}

void FeedFish(){
	//_rtcController.SetLastRun(AccessoryType::Feeder);

	/*Mem:NextRunMemory mem = RTCExt::FindNextRunInfo(AccessoryType::Feeder);
	
	long countDown = mem.CountDown;
	
	long nextRun = mem.NextRun;

	RTCExt::NextFeedInfo.LastRun = RTCExt::GetRTCTime();*/

}




