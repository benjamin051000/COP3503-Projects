#include "TGAImage.h"

TGAImage::TGAImage(const char* filename) {
	ifstream file(filename, ios_base::binary | ios_base::ate);
	if (!file.is_open()) {
		throw "Error opening file.";
	}

	//	Get total bytes with tellg
	auto totalBytes = file.tellg(); //useful? idk
	//	Seek to beginning of file
	file.seekg(0);

	/*---Load Header---*/
	header = TGAHeader(file);

	//Load the actual pixels
	numPixels = header.width * header.height;
	pixelData = new Pixel[numPixels];
	for (unsigned int i = 0; i < numPixels; i++) {
		char b, g, r;
		file.read(&b, sizeof(b));
		file.read(&g, sizeof(g));
		file.read(&r, sizeof(r));
		pixelData[i] = Pixel(b, g, r);
	}
}

bool TGAImage::writeFile(const char* name) {
	ofstream newFile(name, ios_base::binary);

	if (!newFile.is_open()) {
		return false;
	}

	/*---Write Header---*/
	header.writeHeader(newFile);

	for (unsigned int i = 0; i < numPixels; i++) {
		newFile.write((char*)&pixelData[i].b, sizeof(pixelData[i].b));
		newFile.write((char*)&pixelData[i].g, sizeof(pixelData[i].g));
		newFile.write((char*)&pixelData[i].r, sizeof(pixelData[i].r));

	}
	return true;
}

TGAImage::TGAHeader::TGAHeader(ifstream& file) {

	file.read(&idLength, sizeof(idLength));
	
	file.read(&colorMapType, sizeof(colorMapType));
	
	file.read(&dataTypeCode, sizeof(dataTypeCode));

	file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));

	file.read((char*)&colorMapLength, sizeof(colorMapLength));

	file.read(&colorMapDepth, sizeof(colorMapDepth));

	file.read((char*)&xOrigin, sizeof(xOrigin));
	file.read((char*)&yOrigin, sizeof(yOrigin));

	file.read((char*)&width, sizeof(width));
	file.read((char*)&height, sizeof(height));

	file.read(&bitsPerPixel, sizeof(bitsPerPixel));

	file.read(&imageDescriptor, sizeof(imageDescriptor));
}

void TGAImage::TGAHeader::writeHeader(ofstream& file) {
	file.write(&idLength, sizeof(idLength));

	file.write(&colorMapType, sizeof(colorMapType));

	file.write((char*)&colorMapOrigin, sizeof(colorMapOrigin));

	file.write((char*)&colorMapLength, sizeof(colorMapLength));

	file.write(&colorMapDepth, sizeof(colorMapDepth));

	file.write((char*)&xOrigin, sizeof(xOrigin));
	file.write((char*)&yOrigin, sizeof(yOrigin));

	file.write((char*)&width, sizeof(width));
	file.write((char*)&height, sizeof(height));

	file.write(&bitsPerPixel, sizeof(bitsPerPixel));

	file.write(&imageDescriptor, sizeof(imageDescriptor));
}
