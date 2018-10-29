#pragma once
#include "Pixel.h"
#include <fstream>
#include <iostream>
using namespace std;

struct TGAImage {

	struct TGAHeader {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;

		short xOrigin;
		short yOrigin;
		
		short width;
		short height;
		
		char bitsPerPixel;
		char imageDescriptor;

		TGAHeader(ifstream& file);
		TGAHeader() {}

		void writeHeader(ofstream& file);

		//friend ostream& operator<<(ostream& os, TGAHeader&);
		void printHeader();
	};

	TGAHeader header;
	unsigned int numPixels;
	Pixel* pixelData;

	//Constructor: Takes a filename, loads the data
	TGAImage(const char* file);

	bool writeFile(const char* name);
};

