#include "BinReader.h"
#include "BinWriter.h"
#include <iostream>
#include <vector>

using namespace std;

vector<int> find(vector<unsigned char>& file, char* data);
void findAndReplace(vector<unsigned char>& file, vector<int>& occurances, char* data, char* replaceData);

int main(int argc, char** argv)
{
	char* inputFile = argv[1];

	string option = argv[2];

	char* data1 = argv[3];

	char* replaceData;

	BinReader in(inputFile);
	vector<unsigned char> file;

	//read whole file and save in vector
	while (in.isOpen()) {
		char byte = in.readByte();
		file.push_back(byte);
	}

	vector<int> occurances = find(file, data1);

	if (option == "fr") {
		replaceData = argv[4];
		vector<int> occurances = find(file, data1);
		findAndReplace(file, occurances, data1, replaceData);
	}
	else if (option[0] == 'f') {

		for (int i = 0; i < occurances.size() - 1; i++) {
			cout << occurances.at(i) << " ";
		}

	}



	return 0;
}

vector<int> find(vector<unsigned char>& file, char* data) {

	int dataLength = strlen(data);

	vector<int> occurances;

	for (int i = 0; i < (file.size()-1) * 8; i++) {


		int occ = 0;
		for (int k = 0; k < dataLength; k++) {

			int realI = (i + k) / 8;
			int realJ = (i + k) % 8;



			if (realI >= file.size() )
				break;
			
			char e = file[realI];
			
			if ((data[k] == '1' && ((e >> realJ) & 1)) ||(data[k] == '0' && !((e >> realJ) & 1))) {
				if (occ == dataLength-1) {
					occurances.push_back(i + 1);
					i = i + dataLength - 1;
				}
				occ++;
			}
			else
			{
				break;
			}

		}


	}
	return occurances;
}

void writeData(char* replaceData, BinWriter& out) {
	int dataLength = strlen(replaceData);
	for (int i = 0; i < dataLength; i++) {
		if (replaceData[i] == '1') {
			out.writeBit(true);
		}
		else if (replaceData[i] == '0') {
			out.writeBit(false);
		}
	}
}

void findAndReplace(vector<unsigned char>& file, vector<int>& occurances, char* data, char* replaceData) {

	int dataLength = strlen(data);
	int replaceDataLenght = strlen(replaceData);

	int occuranceCounter = 1;
	int nextOccurnace = occurances.at(0);
	
	BinWriter out("test_out.bmp");

	for (int i = 0; i < (file.size() - 1) * 8; i++) {

		if (i == nextOccurnace - 1) {
			writeData(replaceData, out);
			i = i + dataLength-1;

			if (occuranceCounter < occurances.size())
			{
				nextOccurnace = occurances.at(occuranceCounter);
			}
			occuranceCounter++;
		}
		else
		{
			int realI = i / 8;
			int realJ = i % 8;
			out.writeBit(((file.at(realI) >> realJ)&1));
		}

	}

}