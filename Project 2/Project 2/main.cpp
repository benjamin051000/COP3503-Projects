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
	
	return 0;
}



/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles 
Methods: http://www.simplefilter.de/en/basics/mixmods.html */

void task1() {
	TGAImage top("input\\layer1.tga"), bottom("input\\pattern1.tga"),
		correct("examples\\EXAMPLE_part1.tga");

	TGAImage output = top.multiply(bottom);

	if (output.compareTo(correct) == 0) {
		output.writeFile("output\\part1.tga");
		cout << "Task 1 complete." << endl;
	}
	else {
		cout << "Task 1 has errors." << endl;
	}
}

void task2() {
	TGAImage top("input\\layer2.tga"), bottom("input\\car.tga"),
		correct("examples\\EXAMPLE_part2.tga");

	TGAImage output = top.subtract(bottom); //may be backwards

	if (output.compareTo(correct) == 0) {
		output.writeFile("output\\part2.tga");
		cout << "Task 2 complete." << endl;
	}
	else {
		cout << "Task 2 has errors." << endl;
	}
}

void task3() {
	TGAImage a("input\\layer1.tga"), b("input\\pattern2.tga"), c("input\\text.tga"), 
		correct("examples\\EXAMPLE_part3.tga");
	
	TGAImage output = c.screen(a.multiply(b));

	if (output.compareTo(correct) == 0) {
		output.writeFile("output\\part3.tga");
		cout << "Task 3 complete." << endl;
	}
	else {
		cout << "Task 3 has errors." << endl;
	}
}

void task4() {
	TGAImage a("input\\layer2.tga"), b("input\\circles.tga"), c("input\\pattern2.tga"),
		correct("examples\\EXAMPLE_part4.tga");

	TGAImage output = c.subtract(a.multiply(b)); //subtract may be backwards

	if (output.compareTo(correct) == 0) {
		output.writeFile("output\\part4.tga");
		cout << "Task 4 complete." << endl;
	}
	else {
		cout << "Task 4 has errors." << endl;
	}
}

void task5() {
	TGAImage a("input\\layer1.tga"), b("input\\pattern1.tga"),
		correct("examples\\EXAMPLE_part5.tga");

	TGAImage output = a.overlay(b);

	if (output.compareTo(correct) == 0) {
		output.writeFile("output\\part5.tga");
		cout << "Task 5 complete." << endl;
	}
	else {
		cout << "Task 5 has errors." << endl;
	}
}

void task6() {
}

void task7() {
}

void task8() {
}

void task9() {
}

void task10() {
}
