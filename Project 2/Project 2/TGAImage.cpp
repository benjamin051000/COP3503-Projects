#include "TGAImage.h"

TGAImage::TGAImage(const char* a) {
	ifstream file(a, ios_base::binary | ios_base::ate);
	if (!file.is_open()) {
		throw "Error opening file.";
	}

	/*---Load Header---*/

	//	Get total bytes with tellg
	auto totalBytes = file.tellg();
	//	Seek to beginning of file
	file.seekg(0);



	short w, h;
	file.read((char*)&w, sizeof(w));
	file.read((char*)&h, sizeof(h));

	header = TGAHeader(w, h);

	//Load the actual pixels
	pixelData = new Pixel[header.width * header.height];
}

TGAImage::TGAHeader::TGAHeader(char a, char b, char c, short d, short e, char f, short g, short h, short i, short j, char k, char l) {
}

TGAImage::TGAHeader::TGAHeader(short w, short h) {
	width = w;
	height = h;
}

TGAImage::TGAHeader::TGAHeader() {
}
