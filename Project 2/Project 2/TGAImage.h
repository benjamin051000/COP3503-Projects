#pragma once
#include "Pixel.h"
#include <fstream>
#include <iostream>
using namespace std;

class TGAImage {

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
		TGAHeader(const TGAHeader& a);
		TGAHeader() {}

		void writeHeader(ofstream& file);

		//friend ostream& operator<<(ostream& os, TGAHeader&);
		void printHeader();
	};

	TGAHeader header;
	unsigned int numPixels;
	Pixel* pixelData;

public:
	//Constructor: Takes a filename, loads the data
	//TGAImage(short width, short height);
	TGAImage();
	TGAImage(const TGAHeader& header);
	TGAImage(const TGAImage& a);
	TGAImage(const char* file);
	~TGAImage();

	bool writeFile(const char* name);

	/*Image Manipulation*/
	void multiply(TGAImage& a);
	void subtract(TGAImage& a);
	void screen(TGAImage& a);
	void overlay(TGAImage& a);
	void add(unsigned int r, unsigned int g, unsigned int b);
	void scale(float r = 1, float g = 1, float b = 1);
	void flip();

	/*Channels*/
	TGAImage getRedChannel();
	TGAImage getBlueChannel();
	TGAImage getGreenChannel();

	/*Compare*/
	unsigned int compareTo(TGAImage& correct);
};

