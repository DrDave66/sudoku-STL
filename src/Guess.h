#ifndef _GUESS
#define _GUESS

#include <string>
#include <cstring>
using namespace std;

class Guess
{
public:
	Guess(string _puzzleString, string _square, string _guess);
	Guess();
	Guess(const Guess&);
	Guess& operator=(const Guess& cpy) ;
	string toString();

	string puzzleString;
	string square;
	string guess;
};

#endif // _GUESS

