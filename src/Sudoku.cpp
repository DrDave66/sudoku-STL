#include "Sudoku.h"
#define NOTIMING

Sudoku::Sudoku() {
	createVectors();
	clearPuzzle();
	srand((uint32_t)time(NULL));
}

Sudoku::Sudoku(string puzzle) {
	createVectors();
	setPuzzle(puzzle);
	srand((uint32_t)time(NULL));
}

void Sudoku::createVectors(void) {
	// create vector of squares
	squares = crossProduct(rows, cols);
	// create unitlist vector
	vector<string> temp;
	// for each col across the rows
	for (char c : cols) {
		temp = crossProduct(rows, string(1, c));
		unitlist.push_back(temp);
	}
	// for each row across the cols
	for (char r : rows) {
		temp = crossProduct(string(1, r), cols);
		unitlist.push_back(temp);
	}
	// for each 9x9 square
	vector<string> sr; // = { "ABC","DEF","GHI" };
	vector<string> sc; // = { "123", "456", "789" };
	sr.push_back("ABC");
	sr.push_back("DEF");
	sr.push_back("GHI");
	sc.push_back("123");
	sc.push_back("456");
	sc.push_back("789");
	for (string r : sr) {
		for (string c : sc) {
			temp = crossProduct(r, c);
			unitlist.push_back(temp);
		}
	}
	// make unit list dictionary - all units that contain the square
	for (string sq : squares) {
		vector<vector<string> > tempUnitList;
		tempUnitList.clear();
		for (vector<string>  ul : unitlist) {
			for (string l : ul) {
				if (l == sq) {
					tempUnitList.push_back(ul);
				}
			}
		}
		units[sq] = tempUnitList;
	}
	// make peer dictionary
	for (string s : squares) {
		set<string> vec; // use a set so there are no duplicates
		for (vector<string> u : units[s]) {
			for (string l : u) {
				if (l != s) {
					vec.insert(l);
				}
			}
		}
		vector<string> v(vec.begin(), vec.end());
		peers[s] = v;
	}
	// dict of allowable values
	for (string s : squares) {
		allowableValues[s] = digits;
	}
}

void Sudoku::clearPuzzle(void) {
	for (string s : squares) {
		puzzle[s] = ".";
		allowableValues[s] = digits;
	}
}

vector<string> Sudoku::crossProduct(string a, string b) {
	vector<string> v;
	string s;
	for (auto aa : a) {
		for (auto bb : b) {
			s += aa;
			s += bb;
			v.push_back(s);
			s.clear();
		}
	}
	return v;
}

bool Sudoku::setPuzzle(string p) {
	if (p.size() != 81)
		return false;
	// need to verify only numbers and periods
	clearPuzzle();
	uint32_t str_index = 0;
	for (string s : squares) {
		setValue(s, string(1, p[str_index]));
		str_index++;
	}
	return true;
}

/**********************************************************
**********   Printing Functions ***************************
***********************************************************/
string Sudoku::printableStringVector(vector<string> vec) {
	string s;
	for (string v : vec) {
		s += v;
		s += " ";
	}
	return s;
}

string Sudoku::printableStringSet(set<string> st) {
	string s;
	for (string v : st) {
		s += v;
		s += " ";
	}
	return s;
}

string Sudoku::printableVectorVectorString(vector<vector<string> > vvs) {
	string s;
	for (vector<string> vs : vvs) {
		for (string v : vs) {
			s += v;
			s += " ";
		}
		s += "\n";
	}
	return s;
}

void Sudoku::printPuzzle(string title) {
	cout << endl << title;
	printPuzzle();
}

void Sudoku::printPuzzle(void) {
	string header = "     1   2   3    4   5   6    7   8   9";
	string top = "  =========================================";
	string row_sep = "  || --------- || --------- || --------- ||";
	string col_sep = "||";
	string num_sep = "|";
	cout << endl << header << endl;
	cout << top << endl;
	uint32_t col_num = -1;
	uint32_t row_num = -1;
	string index;
	for (char r : rows) {
		cout << r << " " << col_sep;
		for (char c : cols) {
			index = string(1, r) + string(1, c);
			if (puzzle[index] == "0") {
				cout << "  ";
			}
			else {
				cout << " " << puzzle[index];
			}
			if (col_num > 0 && (col_num - 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
			col_num++;
		}
		row_num++;
		cout << endl;
		if (row_num == 8) {
			cout << top << endl;
		}
		else if ((row_num + 1) % 3 == 0) {
			cout << row_sep << endl;
		}

	}
}

void Sudoku::printAllowableValues(void) {
	string header = "         1           2           3            4           5           6            7           8           9";
	string top = "  =================================================================================================================";
	string row_sep = "  || --------------------------------- || --------------------------------- || --------------------------------- ||";
	string col_sep = "||";
	string num_sep = "|";
	cout << endl << header << endl;
	cout << top << endl;
	uint32_t col_num = -1;
	uint32_t row_num = -1;
	string index;
	for (char r : rows) {
		cout << r << " " << col_sep;
		for (char c : cols) {
			index = string(1, r) + string(1, c);
			if (puzzle[index] == "0") {
				cout << "  ";
			}
			else {
				cout << " " << setw(9) << allowableValues[index];
			}
			if (col_num > 0 && (col_num - 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
			col_num++;
		}
		row_num++;
		cout << endl;
		if (row_num == 8) {
			cout << top << endl;
		}
		else if ((row_num + 1) % 3 == 0) {
			cout << row_sep << endl;
		}

	}
}

void Sudoku::printAllowableValues(string title) {
	cout << endl << title;
	printAllowableValues();
}

/**********************************************************
**********   Solving Functions ***************************
***********************************************************/
bool Sudoku::setValue(string square, string value) {
#ifdef TIMING
	PrecisionTimeLapse ptl;
	ptl.start();
#endif 	
    string* s =&allowableValues[square];
    *s = "";
	puzzle[square] = value;
	size_t t;
    if (value == ".") {
        *s = digits;
    }
    
    for (string p : peers[square]) {
        s = &allowableValues[p];
        t = s->find(value);
        if (t != string::npos) {
            s->replace(t, 1, "");
      	}
	}
#ifdef TIMING
	ptl.stop();
	cout << "setValue," << ptl.elapsedString() << endl;
#endif
	return true;
}

bool Sudoku::solveOnes(void) {
#ifdef TIMING	
	PrecisionTimeLapse ptl;
	ptl.start();
#endif	
	bool retval = false;
	bool solvedSome = true;
	while (solvedSome == true && isPuzzleSolved() == false) {
		solvedSome = false;
		// find squares with only one available value
		for (string sq : squares) {
			if (allowableValues[sq].size() == 1) {
				// and set the value
				solvedSome = true;
				setValue(sq, allowableValues[sq]);
                //break;
			}
		}
		// look through all units and see if any value appears only one time
		string allValues = "";
		for (vector<string> ul : unitlist) {
			for (string u : ul) {
				allValues += allowableValues[u];
			}
			for (char d : digits) {
				// if number appears once
				if (count(allValues.begin(), allValues.end(), d) == 1) {
					// find the square with the value in it
					for (string u : ul) {
						if (count(allowableValues[u].begin(), allowableValues[u].end(), d) == 1) {
							solvedSome = true;
							setValue(u, string(1, d));
                            break;
						}
					}
				}
			}
		}
		retval |= solvedSome;
	}
#ifdef TIMING	
	ptl.stop();
	cout << "solveOnes,"  << ptl.elapsedString() << endl;
#endif
	return solvedSome;
}

bool Sudoku::isPuzzleSolved(void) {
	// a puzzle is solved if each unit in unitlist contains values of 1-9
    string val = "123456789";
	for (vector<string> ul : unitlist) {
        val = "123456789";
		for (string u : ul) {
            size_t vp = val.find(puzzle[u]);
            if(vp != string::npos) {
                val = val.replace(vp,1,"");
            } else {
                return false;
            }

		}
        if(val.length() != 0)
            return false;
	}
    return true;
}

string Sudoku::getPuzzleText(void) {
	string retval;
	for (string s : squares) {
		retval += puzzle[s];
	}
	return retval;
}

string Sudoku::getAllowableGuessesText(void) {
	string retval;
	string delim = "|";
	for (string s : squares) {
		if (allowableValues[s] != "") {
			retval += allowableValues[s];
		} else {
			retval += "0";
		}
		retval += delim;
	}
	return retval;
}

string Sudoku::getPackedPuzzle(void) {
	string retval;
	retval = getPuzzleText() + "_" + getAllowableGuessesText();
	return retval;
}

void Sudoku::unpackPuzzle(string packed) {
	size_t us = packed.find('_');
	string puzzleString = packed.substr(0,us);
	string allowString = packed.substr(us+1);
	vector<string> allow;
	for ( int i = 0 ; i < 81 ; i++) {
		puzzle[squares[i]] = puzzleString.substr(i,1);
	}
	size_t vstart = 0;
	size_t vend = -1;
	string temp;
	for( int i = 0 ; i < 81 ; i++) {
		vend = allowString.find('|',vstart);
		temp = allowString.substr(vstart, vend - vstart);
		if (temp == "0") {
			allowableValues[squares[i]] = "";
		} else {
			allowableValues[squares[i]] = temp;
		}
		vstart = vend+1;
	}
}

bool Sudoku::removeGuess(string square, string value){
	bool retval = true;
	string temp = allowableValues[square];
	if (temp.find(value) == string::npos)
		retval = false;
	else {
		temp = allowableValues[square];
		size_t t = temp.find(value);
		if (t != string::npos) {
			temp.replace(t, 1, "");
			allowableValues[square] = temp;
			retval = true;
		} else {
			retval = false;
		}
	}
	return retval;
}

bool Sudoku::guessesRemain(void) {
	for (string s : squares) {
		if(allowableValues[s].length() > 1)
            return true;
	}
	return false;
}

Guess Sudoku::getGuess() { // returns square, value
	// guess is returned as square,value in an array
	uint32_t minCount = 9;
	// iterate through squares and get lowest count > 1
	size_t len;
	for (string s : squares) {
		len = allowableValues[s].size();
		if ( len > 1 ) {
			if (len < minCount) 
			{
				minCount = (uint32_t)len;
			}
		}
	}
	vector<string> subset;
	for (string s : squares) {
		if (allowableValues[s].size() == minCount) {
			subset.push_back(s);
		}
	}
	// select random vector
	string square = subset[rand() % subset.size()];
	char t = allowableValues[square][rand() % allowableValues[square].size()];
	string pt = getPackedPuzzle();
	newGuess = Guess(pt, square, string(1,t));
	return newGuess;
}

bool Sudoku::popGuess() {
	Guess lastGuess = guessList.back();
	if (lastGuess.puzzleString.length() == 0 || lastGuess.square.length() == 0 || lastGuess.guess.length() == 0 )
		return false;
	else {
		unpackPuzzle(lastGuess.puzzleString);
		removeGuess(lastGuess.square, lastGuess.guess);
		guessList.pop_back();
	}
	return true;
}

void Sudoku::pushGuess(Guess const *guess) {
	Guess g;
	g.guess = guess->guess;
	g.square = guess->square;
	g.puzzleString = string(guess->puzzleString);
	guessList.push_back(g);
}

void Sudoku::printGuessList() {
	for (Guess& g : guessList) {
		cout << g.square << ":" << g.guess << " ";
	}
	cout << endl << flush;
}

bool Sudoku::solvePuzzle() {
	solveOnes();
	if (isPuzzleSolved())
		return true;
	else 
		startGuessing();
	return isPuzzleSolved();
}

bool Sudoku::startGuessing() {
	guessList.clear();
	while(!isPuzzleSolved()) {
		while (guessesRemain()) {
			Guess g = getGuess();
			pushGuess(&g);
			setValue(g.square, g.guess);
			solveOnes();
			if (isPuzzleSolved() == false && guessesRemain() == false) {
				popGuess();
			}
		}
		if (isPuzzleSolved() == false) {
			if (guessList.size() == 0) {
			}
			if(popGuess() == false) {
				return false;
			}
		}
			
	}
	return isPuzzleSolved();
}
 void Sudoku::test(void) {

 }
