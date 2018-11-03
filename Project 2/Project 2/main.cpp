#include <iostream>
#include "TGAImage.h"
using namespace std;

int main(int argc, char** argv) {
	/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles 
	Functions: http://www.simplefilter.de/en/basics/mixmods.html */

	//TGAImage image(argv[1]);

	TGAImage image("input\\layer2.tga"), image2("input\\car.tga");
	cout << "Created images." << endl;
	/*image.header.printHeader();*/
	
	//cout << image.pixelData[image.numPixels - 1].r << endl;

	

	//Task 1
	TGAImage output = image.multiply(image2);

	if (output.writeFile("part2.tga")) {
		cout << "\nCopied into output." << endl;
	}
	else {
		cout << "An error occurred when copying the file." << endl;
	}


	return 0;
}