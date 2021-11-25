#ifndef _SUDOKU
#define _SUDOKU
#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <array>

using namespace std;
#include "Guess.h"
#include "PrecisionTimeLapse.h"

class Sudoku
{
public:
	Sudoku();
	Sudoku(string puzzle);
	void clearPuzzle();
	void createVectors(void);
	vector<string> crossProduct(string a, string b);

	bool setPuzzle(string p);
	bool setValue(string square, string value);
	void printPuzzle(void);
	void printPuzzle(string title);
	void printAllowableValues(void);
	void printAllowableValues(string title);
	bool solveOnes(void);
	string printableStringVector(vector<string> vec);
	string printableVectorVectorString(vector<vector<string> >);
	string printableStringSet(set<string> st);
	bool isPuzzleSolved(void); 
	string getPuzzleText(void);
	string getAllowableGuessesText(void);
	string getPackedPuzzle(void);
	void unpackPuzzle(string);
	bool removeGuess(string, string);
	bool guessesRemain(void);
	Guess getGuess();
	bool popGuess();
	void pushGuess(Guess const*);
	bool solvePuzzle();
	bool startGuessing();
	void printGuessList();
	void test();
private:

	map<string, string> puzzle; // unit, value
	string digits = "123456789";
	string rows = "ABCDEFGHI";
	string cols = "123456789";
	vector<string> squares;
	vector<vector<string> > unitlist;
	map<string, vector<vector<string> > > units; // square, squares in unit
	map<string, vector<string> > peers; // square, squares in peers
	map<string, string> allowableValues; // square, string of allowable values
	vector<Guess> guessList; // ordered list of guesses
	Guess newGuess;
	array<char, 9> digitArray = { '1','2','3','4','5','6','7','8','9' };
};

#endif // _SUDOKU
