/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "AIB.h"
#include "Arduino.h"

AIB_::AIB_(int typeInterface, Print &print) {
	_typeInterface = typeInterface;
	_printer = &print;
	_currentMethod = 0;
	//Serial.begin(9600);
}

void AIB_::setSerialSpeed(int serialSpeed) {
	_serialSpeed = serialSpeed;
	Serial.begin(_serialSpeed);
}

int AIB_::prepareConnection(void) {

	String type = "";
	int ret = 0;

	switch(_typeInterface) {

		case 1:
			type + "Produc";
			_printer->println("Production profile = Waiting for initializing!");
			ret = 0;
		break;

		case 2:
			type + "Test";
			_printer->print("Testing profile\n");
			ret = 1;

      /*_printer->print("Esperando por data => ");
      if (Serial.available() > 0) {
        char la = Serial.read();
        Serial.print("I received: ");
        Serial.println(la);
			}*/

		break;

		default:
			type + "Error";
			_printer->print("Error || No matching profile\n");
			ret = 0;
		break;
	}

	delay(5000);
	return ret;
}

void AIB_::setAPIDelimiter(char delimiter) {
	_delimiter = delimiter;
}

void AIB_::sendInt(int value, bool returnLine) {
	String newLine = ( returnLine == false ) ? "" : "\n";
	_printer->print((String)value);
}

void AIB_::sendChar(char value, bool returnLine) {
	String newLine = ( returnLine == false ) ? "" : "\n";
	_printer->print((String)value);
}

void AIB_::send(String value, bool returnLine) {
	String newLine = ( returnLine == false ) ? "" : "\n";
	_printer->print((String)value);
}

void AIB_::start(void) {
	_printer->print('a');
}

void AIB_::startWithInt(int value) {
	sendInt( value, true );
}

void AIB_::startWithChar(char value) {
	sendChar( value, true );
}

void AIB_::startWithString(String value) {
	send( value, true );
}

char AIB_::getDelimiter(void) {
	return _delimiter;
}

void AIB_::prettySerial(void) {
	Serial.print("10\n");
}

void AIB_::addNameMethod(String method) {
	_methods[_currentMethod] = method;
	_currentMethod++;
}

int AIB_::getReferenceMethod(String method) {
	for (int i =0; i <= ARRAYSIZE; i++ ) {
		if ( _methods[i] == method ) {
			return i;
		}
	}
	return -1;
}

String AIB_::getActionFromAPI(String input) {
	return _explode(input, 0);
}

String AIB_::getValueFromAPI(String input, int index) {
	return _explode(input, index);	
}

String AIB_::_explode(String input, int index) {

	int maxIndex = input.length();
    int j = 0;
    String chunkVal = "";
    char delimiter = getDelimiter();

    for (int i = 0; i <= maxIndex && j <= index; i++) {
        
        chunkVal.concat(input[i]);

        if ( input[i] == delimiter ) {
            
            j++;

            if ( j > index ) {
                chunkVal.trim();
                return chunkVal;
            }

            chunkVal = "";
        }
        else if ( (i == maxIndex) && (j < index) ) {
            chunkVal = "";
            return chunkVal;
        }
    }   
}
