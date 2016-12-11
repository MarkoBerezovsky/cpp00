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

/*
void square(int a, int b) {
	printf("#");
}
*/