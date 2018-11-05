#include "TGAImage.h"

TGAImage::TGAImage() {
	header = TGAHeader();
}

TGAImage::TGAImage(const TGAHeader& header) {
	this->header = TGAHeader(header);
	numPixels = header.width * header.height;
	pixelData = new Pixel[numPixels];
}

TGAImage::TGAImage(const TGAImage& a) {
	header = a.header;
	numPixels = a.numPixels;
	pixelData = new Pixel[numPixels];

	for (unsigned int i = 0; i < numPixels; i++) {
		pixelData[i] = Pixel(a.pixelData[i].b, a.pixelData[i].g, a.pixelData[i].r);//a.pixelData[i];
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
		unsigned char b, g, r;
		file.read((char*)&b, sizeof(b));
		file.read((char*)&g, sizeof(g));
		file.read((char*)&r, sizeof(r));
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

TGAImage TGAImage::multiply(const TGAImage& a) const {
	TGAImage output(a.header);

	for (unsigned int i = 0; i < output.numPixels; i++) {
		float norm1b = pixelData[i].b / 255.f,
			   norm1g = pixelData[i].g / 255.f,
			   norm1r = pixelData[i].r / 255.f;

		float norm2b = a.pixelData[i].b / 255.f,
			   norm2g = a.pixelData[i].g / 255.f,
			   norm2r = a.pixelData[i].r / 255.f;

		unsigned char multB = (norm1b * norm2b * 255.f) + 0.5f,
					multG = (norm1g * norm2g * 255.f) + 0.5f,
					multR = (norm1r * norm2r * 255.f) + 0.5f;

		output.pixelData[i].b = multB;
		output.pixelData[i].g = multG;
		output.pixelData[i].r = multR;
	}

	return output;
} 

TGAImage TGAImage::subtract(TGAImage & a) {
	TGAImage output(a.header);

	for (unsigned int i = 0; i < output.numPixels; i++) {

		int topR = (int)a.pixelData[i].r,
			bottomR = (int)pixelData[i].r;
		int outputR = topR - bottomR;
		if (outputR < 0)
			outputR = 0;
		
		int topG = (int)a.pixelData[i].g,
			bottomG = (int)pixelData[i].g;
		int outputG = topG - bottomG;
		if (outputG < 0)
			outputG = 0;

		int topB = (int)a.pixelData[i].b,
			bottomB = (int)pixelData[i].b;
		int outputB = topB - bottomB;
		if (outputB < 0)
			outputB = 0;

		output.pixelData[i].r = outputR;
		output.pixelData[i].g = outputG;
		output.pixelData[i].b = outputB;
	}

	return output;
}

TGAImage TGAImage::screen(TGAImage & a) {
	// 1-(1-A)*(1-B)
	TGAImage output(a.header);

	for (unsigned int i = 0; i < output.numPixels; i++) {
		float norm1b = pixelData[i].b / 255.f,
			norm1g = pixelData[i].g / 255.f,
			norm1r = pixelData[i].r / 255.f;

		float norm2b = a.pixelData[i].b / 255.f,
			norm2g = a.pixelData[i].g / 255.f,
			norm2r = a.pixelData[i].r / 255.f;

		unsigned char multB = (1 - (1 - norm1b) * (1 -norm2b)) * 255.f + 0.5f,
			multG = (1 - (1 - norm1g) * (1 - norm2g)) * 255.f + 0.5f,
			multR = (1 - (1 - norm1r) * (1 - norm2r)) * 255.f + 0.5f;

		output.pixelData[i].b = multB;
		output.pixelData[i].g = multG;
		output.pixelData[i].r = multR;
	}

	return output;
}

TGAImage TGAImage::overlay(TGAImage & a) {
	return NULL;
}

unsigned int TGAImage::compareTo(TGAImage& correct) {
	unsigned int failCount = 0;
	for (unsigned int i = 0; i < numPixels; i++) {
		bool rMatch = this->pixelData[i].r == correct.pixelData[i].r;
		//cout << (int)pixelData[i].r << '\t' << (int)correct.pixelData[i].r << endl;;
		bool gMatch = this->pixelData[i].g == correct.pixelData[i].g;
		bool bMatch = this->pixelData[i].b == correct.pixelData[i].b;

		if (!rMatch || !gMatch || !bMatch) {
			failCount++;
		}
	}
	return failCount;
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

TGAImage::TGAHeader::TGAHeader(const TGAHeader& a) {
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


