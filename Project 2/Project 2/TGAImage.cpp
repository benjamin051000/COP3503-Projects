#include "TGAImage.h"

TGAImage::TGAImage(short width, short height) {
	header = TGAHeader();
	header.width = width;
	header.height = height;

	numPixels = header.width * header.height;
	pixelData = new Pixel[numPixels];
}

TGAImage::TGAImage() {
	header = TGAHeader();

}

TGAImage::TGAImage(const TGAImage & a) {
	header = a.header;
	numPixels = a.numPixels;
	pixelData = new Pixel[numPixels];

	for (unsigned int i = 0; i < numPixels; i++) {
		pixelData[i] = Pixel(a.pixelData[i].r, a.pixelData[i].g, a.pixelData[i].b);//a.pixelData[i];
	}
}

TGAImage::TGAImage(const char* filename) {
	ifstream file(filename, ios_base::binary | ios_base::ate);
	if (!file.is_open()) {
		throw "Error opening file.";
	}

	//	Get total bytes with tellg
	auto totalBytes = file.tellg(); //useful? idk
	
	file.clear(); //Clears any fail bits
	//	Seek to beginning of file
	file.seekg(0, ios_base::beg);

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
		//cout << "Pixel " << i << " {" << (int)r << ", " << (int)g << ", " << (int)b << "}" << endl;
	}
}

TGAImage::~TGAImage() {
	delete[] pixelData;
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

TGAImage TGAImage::multiply(TGAImage & a) {
	TGAImage output(header.width, header.height);
	output.header = TGAHeader(header); //Should this be copied? 
	
	for (unsigned int i = 0; i < this->numPixels; i++) {
		double norm1r = (int)(pixelData[i].r) / 255,
			   norm1g = (int)(pixelData[i].g) / 255,
			   norm1b = (int)(pixelData[i].b) / 255;
		double norm2r = (int)(a.pixelData[i].r) / 255,
			   norm2g = (int)(a.pixelData[i].g) / 255,
			   norm2b = (int)(a.pixelData[i].b) / 255;

		int multR = norm1r * norm2r * 255, //Is this correct? idk man
			multG = norm1g * norm2g * 255,
			multB = norm1b * norm2b * 255;

		output.pixelData[i].r = multR; //Cast to unsigned char?
		output.pixelData[i].g = multG;
		output.pixelData[i].b = multB;
	}
	return output;
}

TGAImage TGAImage::subtract(TGAImage & a) {
	return NULL;
}

TGAImage TGAImage::screen(TGAImage & a) {
	return NULL;
}

TGAImage TGAImage::overlay(TGAImage & a) {
	return NULL;
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

TGAImage::TGAHeader::TGAHeader(TGAHeader& a) {
	idLength = a.idLength;

	colorMapType = a.colorMapType;
	dataTypeCode = a.dataTypeCode;

	colorMapOrigin = a.colorMapOrigin;
	colorMapLength = a.colorMapLength;
	colorMapDepth = a.colorMapDepth;

	xOrigin = a.xOrigin;
	yOrigin = a.yOrigin;

	width = a.width;
	height = a.height;

	bitsPerPixel = a.bitsPerPixel;
	imageDescriptor = a.imageDescriptor;
}

void TGAImage::TGAHeader::writeHeader(ofstream& file) {
	file.write(&idLength, sizeof(idLength));

	file.write(&colorMapType, sizeof(colorMapType));

	file.write(&dataTypeCode, sizeof(dataTypeCode));

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

void TGAImage::TGAHeader::printHeader() {
	cout << "ID Length: " << (int)idLength << endl;
	cout << "Color Map Type: " << (int)colorMapType << endl;
	cout << "Data type code: " << (int)dataTypeCode << endl;
	cout << "Color Map Origin: " << (int)colorMapOrigin << endl;
	cout << "Color Map Length: " << (int)colorMapLength << endl;
	cout << "Color Map Depth: " << (int)colorMapDepth << endl;
	cout << "X Origin: " << (int)xOrigin << endl;
	cout << "Y Origin: " << (int)yOrigin << endl;
	cout << "Width: " << (int)width << endl;
	cout << "Height: " << (int)height << endl;
	cout << "Bits per pixel: " << (int)bitsPerPixel << endl;
	cout << "Image Descriptor: " << (int)imageDescriptor << endl;
}


