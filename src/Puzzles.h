#ifndef _PUZZLES
#define _PUZZLES

#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Puzzles
{
public:
	Puzzles();
	Puzzles(string fname);
	uint32_t getNumberOfPuzzles(void);
	string getPuzzle(uint32_t num);

private:
	string filename;
	vector<string> puzzles;
	uint32_t numPuzzles;
};

#endif //_PUZZLES