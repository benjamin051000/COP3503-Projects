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
		TGAHeader(TGAHeader& a); //Necessary?
		TGAHeader() {}

		void writeHeader(ofstream& file);

		//friend ostream& operator<<(ostream& os, TGAHeader&);
		void printHeader();
	};

	TGAHeader header;
	unsigned int numPixels;
	Pixel* pixelData;

	//Constructor: Takes a filename, loads the data
	TGAImage(short width, short height);
	TGAImage();
	TGAImage(const TGAImage& a);
	TGAImage(const char* file);
	~TGAImage();

	bool writeFile(const char* name);

	/*Image Manipulation*/
	TGAImage multiply(TGAImage& a);
	TGAImage subtract(TGAImage& a);
	TGAImage screen(TGAImage& a);
	TGAImage overlay(TGAImage& a);
};

