#include <iostream>
#include "TGAImage.h"
using namespace std;

int main(int argc, char** argv) {
	/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles */

	//TGAImage image(argv[1]);

	TGAImage image("input\\layer1.tga"), image2("input\\pattern1.tga");
	cout << "Created images." << endl;
	//image.header.printHeader();
	
	//cout << image.pixelData[image.numPixels - 1].r << endl;

	

	//Task 1
	TGAImage output = image.multiply(image2);

	if (output.writeFile("part1.tga")) {
		cout << "\nCopied into output." << endl;
	}
	else {
		cout << "An error occurred when copying the file." << endl;
	}


	return 0;
}