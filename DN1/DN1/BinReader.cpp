//#include "stdafx.h"
#include "BinReader.h"
#include <string>

BinReader::BinReader(std::string in){
	ifd.open(in, std::ios::binary);
}


BinReader::~BinReader(){
	if (ifd.is_open()) {
		ifd.close();
	}
}

bool BinReader::readBit() {
	if (x < 0) {
		if (ifd.get(var)) {
			x = 7;
		}
		else {
			ifd.close();
			return NULL;
		}
	}
	bool bit = (var >> x) & 1;
	x--;
	return bit;
}

char BinReader::readByte() {
	char byte;
	for (int i = 0; i < 8; i++) {
		bool b = readBit();
		if (b) {
			byte |= 1 << i;
		}
		else {
			byte &= ~(1 << i);
		}
		//byte ^= (-b ^ byte)&(128 >> i);
	}
	return byte;
}

int BinReader::readInt() {
	int integer;
	for (int i = 31; i >= 0; i--) {
		bool bit = readBit();
		if (bit) {
			integer |= 1 << i;
		}
		else
			integer &= ~(1 << i);
	}
	return integer;


}

float BinReader::readFloat() {
	float a = *(float*)readInt();
		return a;
}

bool BinReader::isOpen() {
	return ifd.is_open();
}

