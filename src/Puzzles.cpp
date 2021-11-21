
#include "Puzzles.h"
#include <stdio.h>
#include <stdlib.h>


Puzzles::Puzzles() {
	cout << "blank constructor\n";
	numPuzzles = 0; 
	filename = "";
} 

Puzzles::Puzzles(string fname) { 
	cout << "parameter " << fname << "\n";
	filename = fname;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open()) {
		string str;
		while (getline(file, str)) {
			puzzles.push_back(str);
		}
	}
	numPuzzles = (uint32_t)puzzles.size();
}

uint32_t Puzzles::getNumberOfPuzzles(void) {
	return numPuzzles;
}

string Puzzles::getPuzzle(uint32_t num) {
	return puzzles[num];
}

