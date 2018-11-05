#include <iostream>
#include "TGAImage.h"
using namespace std;

int main(int argc, char** argv) {
	/*
	Task 1: Complete
	Task 2: Complete
	Task 3: Complete
	Task 4: Complete
	Task 5: 
	Task 6: 
	Task 7: 
	Task 8: 
	Task 9: 
	Task 10: 
	*/

	TGAImage image("input\\layer2.tga"), image2("input\\circles.tga"), image3("input\\pattern2.tga");
	TGAImage correct("examples\\EXAMPLE_part4.tga");
	cout << "Loaded files successfully." << endl;
	
	//Task 1
	TGAImage temp = image.multiply(image2);
	TGAImage output = image3.subtract(temp);

	cout << "Total mismatched pixels: " << output.compareTo(correct) << endl; //" out of " << image.numPixels << endl;
	
	if (output.writeFile("part4.tga")) {
		cout << "File written successfully." << endl;
	}

	return 0;
}



/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles 
Methods: http://www.simplefilter.de/en/basics/mixmods.html */