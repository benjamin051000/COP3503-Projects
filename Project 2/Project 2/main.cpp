#include <iostream>
#include "TGAImage.h"
using namespace std;

int main(int argc, char** argv) {
	
	//TGAImage image(argv[1]);

	TGAImage image("input\\car.tga");
	cout << "Created image." << endl;
	if (image.writeFile("corrupt.tga")) {
		cout << "Copied into folder." << endl;
	}
	else {
		cout << "An error occurred when copying the file." << endl;
	}
	
	return 0;
}
