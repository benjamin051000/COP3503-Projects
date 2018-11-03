#include <iostream>
#include "TGAImage.h"
using namespace std;

int main(int argc, char** argv) {
	
	TGAImage image("input\\layer1.tga"), image2("input\\pattern1.tga");
	TGAImage correctMult("examples\\EXAMPLE_part1.tga");
	cout << "Loaded files successfully." << endl;
	
	//Task 1
	TGAImage output = image.multiply(image2);

	cout << "Total mismatched pixels: " << output.compareTo(correctMult) << endl; //" out of " << image.numPixels << endl;
	
	if (output.writeFile("task1.tga")) {
		cout << "File written successfully." << endl;
	}

	return 0;
}



/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles 
Functions: http://www.simplefilter.de/en/basics/mixmods.html */