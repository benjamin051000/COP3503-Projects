#include <iostream>
#include "TGAImage.h"
using namespace std;

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();
void extraCredit();

int main() {
	/*
	Task 1: Complete
	Task 2: Complete
	Task 3: Complete
	Task 4: Complete
	Task 5: --------Error!!!
	Task 6: Complete
	Task 7: Complete
	Task 8: Complete
	Task 9: Complete
	Task 10: Complete
	*/

	task1();
	task2();
	task3();
	task4();
	task5();
	task6();
	task7();
	task8();
	task9();
	task10();
	//extraCredit();
	
	return 0;
}



/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles 
Methods: http://www.simplefilter.de/en/basics/mixmods.html */

void task1() {
	cout << "Test #1...... ";
	TGAImage a("input\\layer1.tga"), b("input\\pattern1.tga"),
		correct("examples\\EXAMPLE_part1.tga");

	a.multiply(b);
	a.writeFile("output\\part1.tga");
	
	if (a.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part1.tga", "examples\\EXAMPLE_part1.tga")) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task2() {
	cout << "Test #2...... ";
	TGAImage a("input\\layer2.tga"), b("input\\car.tga"),
		correct("examples\\EXAMPLE_part2.tga");

	a.subtract(b);
	a.writeFile("output\\part2.tga");

	if (a.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part2.tga", "examples\\EXAMPLE_part2.tga")) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
	
}

void task3() {
	cout << "Test #3...... ";
	TGAImage a("input\\layer1.tga"), b("input\\pattern2.tga"), c("input\\text.tga"), 
		correct("examples\\EXAMPLE_part3.tga");

	a.multiply(b);
	c.screen(a);
	c.writeFile("output\\part3.tga");

	if (c.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part3.tga", "examples\\EXAMPLE_part3.tga")) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task4() {
	cout << "Test #4...... ";
	TGAImage a("input\\layer2.tga"), b("input\\circles.tga"), c("input\\pattern2.tga"),
		correct("examples\\EXAMPLE_part4.tga");

	a.multiply(b);
	c.subtract(a); //subtract may be backwards
	c.writeFile("output\\part4.tga");
	
	if (c.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part4.tga", "examples\\EXAMPLE_part4.tga")) {
		
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task5() {
	cout << "Test #5...... ";
	TGAImage a("input\\layer1.tga"), b("input\\pattern1.tga"),
		correct("examples\\EXAMPLE_part5.tga");

	a.overlay(b);
	a.writeFile("output\\part5.tga");
	
	if (a.compareTo(correct) == 0) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task6() {
	cout << "Test #6...... ";
	TGAImage a("input\\car.tga"),
		correct("examples\\EXAMPLE_part6.tga");

	a.add(0, 200, 0);
	a.writeFile("output\\part6.tga");

	if (a.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part6.tga", "examples\\EXAMPLE_part6.tga")) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task7() {
	cout << "Test #7...... ";
	TGAImage a("input\\car.tga"),
		correct("examples\\EXAMPLE_part7.tga");

	a.scale(4, 1, 0);
	a.writeFile("output\\part7.tga");

	if (a.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part7.tga", "examples\\EXAMPLE_part7.tga")) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task8() {
	cout << "Test #8...... ";
	TGAImage a("input\\car.tga"),
		correctR("examples\\EXAMPLE_part8_r.tga"),
		correctG("examples\\EXAMPLE_part8_g.tga"),
		correctB("examples\\EXAMPLE_part8_b.tga");
	
	TGAImage red = a.getRedChannel(), 
		green = a.getGreenChannel(),
		blue = a.getBlueChannel();

	red.writeFile("output\\part8_r.tga");
	green.writeFile("output\\part8_g.tga");
	blue.writeFile("output\\part8_b.tga");

	if (red.compareTo(correctR) == 0) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task9() {
	cout << "Test #9...... ";
	TGAImage red("input\\layer_red.tga"), green("input\\layer_green.tga"), blue("input\\layer_blue.tga"),
		correct("examples\\EXAMPLE_part9.tga");

	TGAImage combined(red, green, blue);
	combined.writeFile("output\\part9.tga");

	if (combined.compareTo(correct) == 0) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void task10() {
	cout << "Test #10...... ";
	TGAImage a("input\\text2.tga"),
		correct("examples\\EXAMPLE_part10.tga");

	a.flip();
	a.writeFile("output\\part10.tga");

	if (a.compareTo(correct) == 0 && TGAImage::compareFiles("output\\part10.tga", "examples\\EXAMPLE_part10.tga")) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}

void extraCredit() {
	TGAImage tl("input\\car.tga"), tr("input\\circles.tga"), 
		bl("input\\pattern1.tga"), br("input\\text.tga"),
		correct("examples\\EXAMPLE_extraCredit.tga");

	TGAImage combined(tl, tr, bl, br);
	combined.writeFile("output\\extraCredit.tga");

	if (combined.compareTo(correct) == 0) {
		cout << "Passed!" << endl;
	}
	else {
		cout << "Failed!" << endl;
	}
}
