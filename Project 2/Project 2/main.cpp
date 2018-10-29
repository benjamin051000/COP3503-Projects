#include <iostream>
#include "TGAImage.h"
using namespace std;

int main(int argc, char** argv) {
	/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles */

	//TGAImage image(argv[1]);

	TGAImage image("input\\layer1.tga");
	cout << "Created image." << endl;
	image.header.printHeader();
	cout << image.pixelData[image.numPixels - 1].r << endl;

	if (image.writeFile("copy.tga")) {
		cout << "\nCopied into folder." << endl;
	}
	else {
		cout << "An error occurred when copying the file." << endl;
	}

	return 0;
}
