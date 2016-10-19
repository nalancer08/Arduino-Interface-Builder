/*
  AIB.h - Library for Arduino Interface Builder
  Created by Erick C. Sanchez, October 4, 2016.
  MIT License
*/
#ifndef AIB_h
#define AIB_h

#define interfaceProduction 1
#define interfaceTesting 2

#include "SoftwareSerial.h"
//#define SERIAL_BUFFER_SIZE 256
#define ARRAYSIZE 5


class AIB_ {
	public:
		AIB_(int typeInterface, Print &print);

		void setSerialSpeed(int);
		int prepareConnection(void);

		void setAPIDelimiter(char delimiter = '|');
		char getDelimiter(void);

		void start(void);
		void startWithInt(int value);
		void startWithChar(char value);
		void startWithString(String value);

		void sendInt(int value, bool returnLine = false);
		void sendChar(char value, bool returnLine = false);
		void send(String value, bool returnLine = false);

		//bool checkInstance(void);
		void prettySerial(void);
		void addNameMethod(String method);

		String getValueFromAPI(String input, int index = 1);
		String getActionFromAPI(String input);
		int getReferenceMethod(String method);

		char _delimiter;
	private:
		int _typeInterface;
		int _serialSpeed;
		Print* _printer;
		//bool _completeSetup;
		String _explode(String input, int index);

		String _methods[ARRAYSIZE];
		int _currentMethod;
};

extern AIB_ AIB;


#endif
