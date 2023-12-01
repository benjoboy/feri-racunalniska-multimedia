//#include "stdafx.h"
#include "BinWriter.h"
#include <string>
#include <iostream>



BinWriter::BinWriter(std::string out) {
	ofd.open(out, std::ios::binary);
}

BinWriter::~BinWriter(){
	if (x>0) ofd.write(&var, 1);
	ofd.close();
}

void BinWriter::writeBit(bool b) {
	
	if (x == 8) {
		ofd.write(&var, 1);
		x = 0; var = 0;
	}
	/*if (b) {
		var |= 1 << x;
	}
	else {
		var &= ~(1 << x);
	}*/
	var ^= (-b ^ var) & (128 >> x); // nastavimo x-ti bit na b (0 ali 1)
	x++;
}

void BinWriter::writeByte(char b) {
	for (int i = 7; i >=0; i--) {
		bool bit = b & 128 >> i;
		writeBit(bit);
	}
}

void BinWriter::writeInt(int i) {
	for (int j = 31; j >= 0; j--) {
		bool bit = (i >> j) & 1;
		writeBit(bit);
	}
}

void BinWriter::writeFloat(float f) {
	writeInt((int)&f);
}

void BinWriter::setX(int i) {
	x = i;
}