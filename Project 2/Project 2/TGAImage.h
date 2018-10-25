#pragma once
#include "Pixel.h"
#include <fstream>
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

		TGAHeader(short x, short y);
		TGAHeader();
	};

	TGAHeader header;
	Pixel* pixelData;

	//Constructor: Takes a filename, loads the data
	TGAImage(const char* a);
};

