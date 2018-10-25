#include "TGAImage.h"

TGAImage::TGAImage(const char* a) {
	ifstream file(a, ios_base::binary | ios_base::ate);
	if (!file.is_open()) {
		throw "Error opening file.";
	}

	/*---Load Header---*/

	//	Get total bytes with tellg
	auto totalBytes = file.tellg();
	//	Seek to 12 bytes from the beginning of file, where xOrigin begins
	file.seekg(12, ios_base::beg);
	short w, h;
	file.read((char*)&w, sizeof(w));
	file.read((char*)&h, sizeof(h));

	header = TGAHeader(w, h);

	//Load the actual pixels
	pixelData = new Pixel[header.width * header.height];
}

TGAImage::TGAHeader::TGAHeader(short w, short h) {
	width = w;
	height = h;
}

TGAImage::TGAHeader::TGAHeader() {
}
