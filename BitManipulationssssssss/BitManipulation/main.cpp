#include <stdlib.h>
#include <iostream>
#include <Windows.h>

unsigned int Data = 2;
unsigned int selectedBit = 2;
HANDLE hConsole; // used for things

int turnOn(int bit, int bitNum) {

	bit |= 1UL << bitNum;

	return bit;

}

int turnOff(int bit, int bitNum) {

	bit &= ~(1UL << bitNum);

	return bit;
}

int toggle(int bit, int bitNum) {

	bit ^= 1UL << bitNum;

	return bit;
}

int negate(int bit) {
	
	return ~bit;
}

int leftShift(unsigned int bit) {

	return bit << 1;
}

int rightShift(unsigned int bit) {

	return bit >> 1;
}

void outCharColor(unsigned short color, char msg) {

	SetConsoleTextAttribute(hConsole, color);
	std::cout << msg;
	SetConsoleTextAttribute(hConsole, 7); //reset color to white

}

void printBinaryNumber(unsigned int number, int size) {
	
	char* text = new char[size + 1];
	text[size] = '\0';
	for (int i = size - 1; i >= 0; i--) {
		if (number % 2 == 0) {
			text[i] = '0';
		}
		else {
			text[i] = '1';
		}
		number = number / 2;
	}

	int trueSelected = (size - 1) - selectedBit;

	for (int i = 0; i < size; i++) {

		if (i == trueSelected) {
			outCharColor(3, text[i]);
		}
		else {
			std::cout << text[i];
		}
	}

	std::cout << std::endl;

}

int main() {

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) {
		std::cout << "Number: " << (int)Data << "	Binary: ";

		if (GetAsyncKeyState(VK_F1)) {
			//TURN ON
			Data = turnOn(Data, selectedBit);
		}
		else if (GetAsyncKeyState(VK_F2)) {
			Data = toggle(Data, selectedBit);
			//TOGGLE
		}
		else if (GetAsyncKeyState(VK_F3)) {
			Data = turnOff(Data, selectedBit);
			//TURN OFF
		}
		else if (GetAsyncKeyState(VK_F4)) {
			//NEGATE
			Data = negate(Data);
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			//LEFT SHIFT
			Data = leftShift(Data);
		}
		else if (GetAsyncKeyState(VK_RIGHT)) { 
			//RIGHT SHIFT
			Data = rightShift(Data);
		}

		if (GetAsyncKeyState(VK_DOWN)) {
			if (selectedBit < 7) {
				selectedBit += 1;
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			if (selectedBit > 0) {
				selectedBit -= 1;
			}
		}
		// my keyboard's shift keys aren't counted as 2 different inputs, 
		// so i had to use the arrow keys.

		printBinaryNumber(Data, 8);

		Sleep(30);
		system("cls");
	}


	return EXIT_SUCCESS;
}