/*
	AlarmCentral.h
	written by Felipe Faé Schwade
	2016, August 8.
	MIT license

*/
//Including the third party required libraries
#include <Arduino.h>
#include <RCSwitch.h>
#include <SD.h>
#include <SPI.h>
#ifndef AlarmCentral_h
#define AlarmCentral_h
	//A flag used to return undefined received signal
	#define UNDEFINED -1
	/**
		These pins are defined for Arduino R3
		For use it in other boards please change it below
	*/
	#define SD_PIN 4
	#define SD_MOSI 11
	#define SD_MISO 12
	#define SD_CLK 13 

	class AlarmCentral {
		public:
			AlarmCentral(RCSwitch mySwitch);
			void addPIRSensor(int sensor);
			void setLedPins(int greenLed, int redLed);
			void setSirenPin(int sirenPin);
			void setNewControlButtonPin(int newControlButtonPin);
			void begin();
			int getReceivedSignal();
			void treatReceivedSignal(int receivedSignal);
		private:
			RCSwitch _mySwitch;
			int _signalReceived;
			int _newControlButton;
			int _PIRSensors[20];
			int _greenLed;
			int _redLed;
			int _sirenPin;
			int _PIRqty = 1;
			int _controlsqty;
			//The new control variable for a better code understanding
			long int _new_control;
			unsigned long _currentMillis;
			unsigned long _previousMillis;
			int _state;
			//The possible status enum
			enum _Status {
			    ALARM_OFF,
			    ALARM_ON,
			    ALARM_STARTED,
			    NEW_CONTROL_ADDING
			  };
			  
			//All the possible received signals
			enum _receivedSignal {
			    CONTROL_SIGNAL,
			    SENSOR_SIGNAL,
			    NEW_CONTROL_BUTTON_PRESSED
			  };
			//Define the file containing all control codes
			File _myFile;
			long int _controls[];
			void ledBlink(int _led, int s_peed_milis);
			void turnOn(int _pin);
			void turnOff(int _pin);
			void sirenBeep(int _times);
			void SDOpenFileFailed();
			void SDReadFailed();
			void loadData();
			void setAlarmOn();
			void setAlarmOff();
			void startAlarm();
			void addNewControl(int signalReceived);
			void setNewControlAddingState();
			void verifyPin(int pin);
	};

#endif