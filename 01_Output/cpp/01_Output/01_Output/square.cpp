#include <stdio.h>
#include "square.h"
#include <iostream>





void square(int  a, int  b) {
	for (int row = 0; row < a; row++) {
		for (int column = 0; column < b; column++) {
			if (row == 0 || row == a-1) {
				if (column != b-1) {
					std::cout << "#";
				}
				else {
					std::cout << "#"<< std::endl;
				}
			
				
			}
			else {
				if (column == 0) {
					std::cout << "#";
				}
				else if (column == b-1) {
					std::cout << "#" << std::endl;
				}
				else {
					std::cout << " ";
				
				}
			}
		}
	}
}

void printTopBottom(int size) {
	for (int i = 0; i < size; i++) {
		std::cout << "#";
	}
}

void printTwoAtPos(int pos, int len) {
	for (int c = 0; c < len; c++) {
		if (c == pos-1 || c == len - pos) {
			std::cout << "#";
		}
		else {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

void printDiag(int size) {
	for(int row = 2;row<size;row++)
			printTwoAtPos(row, size);    
}

void shape_x(int size) {
	printTopBottom(size);
	std::cout << std::endl;
	printDiag(size);
	printTopBottom(size);
}
/*
void square(int a, int b) {
	printf("#");
}
*/