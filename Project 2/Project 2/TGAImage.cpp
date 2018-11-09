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
		pixelData[i] = Pixel(a.pixelData[i].b, a.pixelData[i].g, a.pixelData[i].r);//bottom.pixelData[i];
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

TGAImage::TGAImage(TGAImage & r, TGAImage & g, TGAImage & b) {
	header = TGAHeader(r.header);
	numPixels = r.numPixels;
	pixelData = new Pixel[numPixels];

	for (unsigned int i = 0; i < numPixels; i++) {
		pixelData[i].r = r.pixelData[i].r;
		pixelData[i].g = g.pixelData[i].g;
		pixelData[i].b = b.pixelData[i].b;
	}
}

TGAImage::TGAImage(TGAImage& tl, TGAImage& tr, TGAImage& bl, TGAImage& br) {
	header = TGAHeader(tl.header);
	header.width *= 2;
	header.height *= 2;
	numPixels = header.width * header.height;
	pixelData = new Pixel[numPixels];

		//If this works, victory royale
	for (unsigned int i = 0; i < numPixels / 2; i++) {
		pixelData[i] = (i % header.height) % (header.width / 2) > 0 ? 
			bl.pixelData[i] : br.pixelData[i]; 
	}

	for (unsigned int i = numPixels / 2; i < numPixels; i++) {
		pixelData[i] = (i % header.height) % (header.width / 2) > 0 ?
			tr.pixelData[i] : tl.pixelData[i];
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

void TGAImage::multiply(TGAImage& bottom) {

	for (unsigned int i = 0; i < numPixels; i++) {
		float norm1b = pixelData[i].b / 255.f,
			   norm1g = pixelData[i].g / 255.f,
			   norm1r = pixelData[i].r / 255.f;

		float norm2b = bottom.pixelData[i].b / 255.f,
			   norm2g = bottom.pixelData[i].g / 255.f,
			   norm2r = bottom.pixelData[i].r / 255.f;

		unsigned char multB = (unsigned char)((norm1b * norm2b * 255.f) + 0.5f),
					multG = (unsigned char)((norm1g * norm2g * 255.f) + 0.5f),
					multR = (unsigned char)((norm1r * norm2r * 255.f) + 0.5f);

		pixelData[i] = Pixel(multB, multG, multR);
	}
} 

void TGAImage::subtract(TGAImage& bottom) {

	for (unsigned int i = 0; i < numPixels; i++) {

		int bottomR = (int)bottom.pixelData[i].r,
			topR = (int)pixelData[i].r;
		int outputR = bottomR - topR;
		if (outputR < 0)
			outputR = 0;
		
		int bottomG = (int)bottom.pixelData[i].g,
			topG = (int)pixelData[i].g;
		int outputG = bottomG - topG;
		if (outputG < 0)
			outputG = 0;

		int bottomB = (int)bottom.pixelData[i].b,
			topB = (int)pixelData[i].b;
		int outputB = bottomB - topB;
		if (outputB < 0)
			outputB = 0;

		pixelData[i].r = outputR;
		pixelData[i].g = outputG;
		pixelData[i].b = outputB;
	}
}

void TGAImage::screen(TGAImage& bottom) {
	// 1-(1-A)*(1-B)

	for (unsigned int i = 0; i < numPixels; i++) {
		float norm1b = pixelData[i].b / 255.f,
			norm1g = pixelData[i].g / 255.f,
			norm1r = pixelData[i].r / 255.f;

		float norm2b = bottom.pixelData[i].b / 255.f,
			norm2g = bottom.pixelData[i].g / 255.f,
			norm2r = bottom.pixelData[i].r / 255.f;

		unsigned char multB = (unsigned char)((1 - (1 - norm1b) * (1 -norm2b)) * 255.f + 0.5f),
			multG = (unsigned char)((1 - (1 - norm1g) * (1 - norm2g)) * 255.f + 0.5f),
			multR = (unsigned char)((1 - (1 - norm1r) * (1 - norm2r)) * 255.f + 0.5f);

		pixelData[i] = Pixel(multB, multG, multR);
	}
}

void TGAImage::overlay(TGAImage& bottom) {

	for (unsigned int i = 0; i < numPixels; i++) {

		float norm1b = bottom.pixelData[i].b / 255.f,
			norm1g = bottom.pixelData[i].g / 255.f,
			norm1r = bottom.pixelData[i].r / 255.f;

		float norm2b = pixelData[i].b / 255.f,
			norm2g = pixelData[i].g / 255.f,
			norm2r = pixelData[i].r / 255.f;

		float newR, newG, newB;

		//Blue channel
		if (norm1b <= 0.5f)
			newB = 2 * norm1b * norm2b * 255 + 0.5f;
		else
			newB = ( 1 - (2 * (1 - norm1b) * (1 - norm2b)) ) * 255 + 0.5f;
		
		pixelData[i].b = newB > 255 ? 255 : (unsigned char)newB;
		
		//Green channel
		if (norm1g <= 0.5f)
			newG = 2 * norm1g * norm2g * 255 + 0.5f;
		else
			newG = ( 1 - (2 * (1 - norm1g) * (1 - norm2g)) ) * 255 + 0.5f;

		pixelData[i].g = newG > 255 ? 255 : (unsigned char)newG;

		//Red channel
		if (norm1r <= 0.5f)
			newR = 2 * norm1r * norm2r * 255 + 0.5f;
		else
			newR = ( 1 - (2 * (1 - norm1r) * (1 - norm2r)) ) * 255 + 0.5f;

		pixelData[i].r = newR > 255 ? 255 : (unsigned char)newR;
		
		/*if (i % 500 == 0)
			cout << (int)pixelData[i].r << '\t' << (int)pixelData[i].g 
			<< '\t' << (int)pixelData[i].b << endl;*/
	}
}

void TGAImage::add(unsigned int r, unsigned int g, unsigned int b) {
	for (unsigned int i = 0; i < numPixels; i++) {
		int newR = (int)pixelData[i].r + r;
		pixelData[i].r = newR > 255 ? 255 : newR;

		int newG = (int)pixelData[i].g + g;
		pixelData[i].g = newG > 255 ? 255 : newG;

		int newB = (int)pixelData[i].b + b;
		pixelData[i].b = newB > 255 ? 255 : newB;
	}
}

void TGAImage::scale(float r, float g, float b) {
	for (unsigned int i = 0; i < numPixels; i++) {
		float newR = (pixelData[i].r / 255.f * r * 255) + 0.5f,
			newG = (pixelData[i].g / 255.f * g * 255) + 0.5f,
			newB = (pixelData[i].b / 255.f * b * 255) + 0.5f;

		pixelData[i].r = newR > 255 ? 255 : (unsigned char)newR;
		pixelData[i].g = newG > 255 ? 255: (unsigned char)newG;
		pixelData[i].b = newB > 255 ? 255 : (unsigned char)newB;
	}
}

void TGAImage::flip() {
	TGAImage flipped(header);
	for (unsigned int i = 0; i < numPixels; i++) {
		flipped.pixelData[numPixels - 1 - i] = pixelData[i];
	}

	for (unsigned int i = 0; i < numPixels; i++) {
		pixelData[i] = flipped.pixelData[i];
	}
}

TGAImage TGAImage::getRedChannel() {
	TGAImage output(*this);
	
	for (unsigned int i = 0; i < numPixels; i++) {
		output.pixelData[i].g = pixelData[i].r;
		output.pixelData[i].b = pixelData[i].r;
	}

	return output;
}

TGAImage TGAImage::getBlueChannel() {
	TGAImage output(*this);

	for (unsigned int i = 0; i < numPixels; i++) {
		output.pixelData[i].r = pixelData[i].b;
		output.pixelData[i].g = pixelData[i].b;
	}

	return output;
}

TGAImage TGAImage::getGreenChannel() {
	TGAImage output(*this);

	for (unsigned int i = 0; i < numPixels; i++) {
		output.pixelData[i].r = pixelData[i].g;
		output.pixelData[i].b = pixelData[i].g;
	}

	return output;
}

unsigned int TGAImage::compareTo(TGAImage& correct) {
	unsigned int failCount = 0;
	for (unsigned int i = 0; i < numPixels; i++) {
		bool rMatch = this->pixelData[i].r == correct.pixelData[i].r;
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