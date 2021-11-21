#include "Guess.h"

Guess::Guess(string _puzzleString, string _square, string _guess) {
	puzzleString = _puzzleString;
	square = _square;
	guess = _guess;
}

Guess::Guess() {
	puzzleString = "";
	square = "";
	guess = "";
}
Guess::Guess(const Guess& g) {
	puzzleString = g.puzzleString;
	square = g.square;
	guess = g.guess;
}

Guess& Guess::operator=(const Guess& cpy) {
	puzzleString = cpy.puzzleString;
	square = cpy.square;
	guess = cpy.guess;
	return *this;
}

string Guess::toString() {
	char ss[1000];
	sprintf(ss,"Square: %s, Guess: %s, Puzzle Text: %s\n",square.c_str(), guess.c_str(), puzzleString.c_str());
	string retval(ss);
	return retval;
}