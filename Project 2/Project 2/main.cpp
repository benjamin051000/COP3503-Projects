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
	Task 5: ---Error!!!
	Task 6: Complete
	Task 7: Complete
	Task 8: 
	Task 9: 
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
	
	return 0;
}



/*Make: https://ufl.instructure.com/courses/357209/pages/makefiles 
Methods: http://www.simplefilter.de/en/basics/mixmods.html */

void task1() {
	TGAImage a("input\\layer1.tga"), b("input\\pattern1.tga"),
		correct("examples\\EXAMPLE_part1.tga");

	a.multiply(b);
	a.writeFile("output\\part1.tga");
	
	if (a.compareTo(correct) == 0) {
		cout << "Task 1 complete." << endl;
	}
	else {
		cout << "Task 1 has errors." << endl;
	}
}

void task2() {
	TGAImage a("input\\layer2.tga"), b("input\\car.tga"),
		correct("examples\\EXAMPLE_part2.tga");

	a.subtract(b); //may be backwards
	a.writeFile("output\\part2.tga");

	if (a.compareTo(correct) == 0) {
		cout << "Task 2 complete." << endl;
	}
	else {
		cout << "Task 2 has errors." << endl;
	}
	
}

void task3() {
	TGAImage a("input\\layer1.tga"), b("input\\pattern2.tga"), c("input\\text.tga"), 
		correct("examples\\EXAMPLE_part3.tga");

	a.multiply(b);
	c.screen(a);
	c.writeFile("output\\part3.tga");

	if (c.compareTo(correct) == 0) {	
		cout << "Task 3 complete." << endl;
	}
	else {
		cout << "Task 3 has errors." << endl;
	}
}

void task4() {
	TGAImage a("input\\layer2.tga"), b("input\\circles.tga"), c("input\\pattern2.tga"),
		correct("examples\\EXAMPLE_part4.tga");

	a.multiply(b);
	c.subtract(a); //subtract may be backwards
	c.writeFile("output\\part4.tga");
	
	if (c.compareTo(correct) == 0) {
		
		cout << "Task 4 complete." << endl;
	}
	else {
		cout << "Task 4 has errors." << endl;
	}
}

void task5() {
	TGAImage a("input\\layer1.tga"), b("input\\pattern1.tga"),
		correct("examples\\EXAMPLE_part5.tga");

	b.overlay(a);
	b.writeFile("output\\part5.tga");
	
	if (b.compareTo(correct) == 0) {
		cout << "Task 5 complete." << endl;
	}
	else {
		cout << "Task 5 has errors." << endl;
	}
}

void task6() {
	TGAImage a("input\\car.tga"),
		correct("examples\\EXAMPLE_part6.tga");

	a.add(0, 200, 0);
	a.writeFile("output\\part6.tga");

	if (a.compareTo(correct) == 0) {
		cout << "Task 6 complete." << endl;
	}
	else {
		cout << "Task 6 has errors." << endl;
	}
}

void task7() {
	TGAImage a("input\\car.tga"),
		correct("examples\\EXAMPLE_part7.tga");

	a.scale(4, 1, 0);
	a.writeFile("output\\part7.tga");

	if (a.compareTo(correct) == 0) {
		cout << "Task 7 complete." << endl;
	}
	else {
		cout << "Task 7 has errors." << endl;
	}
}

void task8() {
	TGAImage a("input\\car.tga"),
		correctR("examples\\EXAMPLE_part8_r.tga"),
		correctG("examples\\EXAMPLE_part8_g.tga"),
		correctB("examples\\EXAMPLE_part8_b.tga");


}

void task9() {
}

void task10() {
	TGAImage a("input\\text2.tga"),
		correct("examples\\EXAMPLE_part10.tga");

	a.flip();
	a.writeFile("output\\part10.tga");

	if (a.compareTo(correct) == 0) {
		cout << "Task 10 complete." << endl;
	}
	else {
		cout << "Task 10 has errors." << endl;
	}
}
