// vcSudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Puzzles.h"
#include "Sudoku.h"
#include "PrecisionTimeLapse.h"
// solved with ones/peers
string grid1 =   "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
string grid3 =   "802050701007082460010900000600001832500000009184300006000004020095610300308090607";
// not solved with ones/peers
string easy505 = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6";
string grid2 =   "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
string hard1 =   ".....6....59.....82....8....45........3........6..3.54...325..6..................";
string easy506 = ".43.8.25.6.............1.949....4.7....6.8....1.2....382.5.............5.34.9.71.";
string solved1 = "981543627723698145645712938368159274417326589592487316854931762236875491179264853";
string solved2 = "968531724514792638237468519326945187185327946479186253891273465753614892642859371";
string solved3 = "487365219932841756165297384524916837319758462876432591793184625641523978258679143";
string solved4 = "647391582125687394938542617264915873891736425753824961319258746486173259572469138";
string solvedx = ".47391582125687394938542617264915873891736425753824961319258746486173259572469138";
#define sPRINTING

#define aSHORTMAIN

#ifdef SHORTMAIN
int main() {

}
#else
int main()
{

	Puzzles p;
	Puzzles pf("../sudoku-puzzles/100000P.txt");
	cout << pf.getNumberOfPuzzles() << " puzzles loaded" << endl;
	if (pf.getNumberOfPuzzles() == 0)
		return 1;
	Sudoku s;
	PrecisionTimeLapse total;
	PrecisionTimeLapse ptl;
	int solved = 0;
	double minTime = 100000.0;
	double maxTime = 0.0;
	double sumTime =  0.0;
	double time;
	total.start();
	for (uint32_t i = 0; i < pf.getNumberOfPuzzles(); i++) {
#ifdef PRINTING
        cout << i+1 << " ";
#endif
		s.setPuzzle(pf.getPuzzle(i));
		ptl.start();
		s.solvePuzzle();
		ptl.stop();
		if (s.isPuzzleSolved() == true)
		{
   			solved += 1;
#ifdef PRINTING
			cout << "SOLVED\n";
#endif
			//s.printPuzzle();
		}
		else {
#ifdef PRINTING
			cout << "NOTSOLVED \n";
#endif
		}
		time = ptl.elapsed();

		minTime = min(minTime, time);
		maxTime = max(maxTime, time);
		sumTime += time;
		//cout << time << " " << sumTime << "  ";
		//cout << "Total time: " << ptl.elapsedString() << " solved " << solved << " out of " << i+1 << endl;
        if(i % 1000 == 0)
            cout << i << endl;
		
	}
	total.stop();
    //cout << " Total time: " << total.elapsed() << " seconds" << endl;
    cout << "Solved " << solved << " out of " << pf.getNumberOfPuzzles() << " puzzles\n";
	cout << "Min time: " << minTime*1000.0 << " ms, Max time: " << maxTime*1000.0 << " ms, Average Time: " << (double)sumTime / (double)solved * 1000 << " ms, Total: " << total.elapsedString(SEC) << " sec" << endl;
}
#endif
//Min time: 0.06397 ms, Max time: 14.2584 ms, Average Time: 0.080051 ms, Total: 12.063358 sec
// added break to loops in solve1   Min time: 0.066761 ms, Max time: 34.5678 ms, Average Time: 0.0777364 ms, Total: 11.696870 sec
// added isSolved to solveones loop Min time: 0.074234 ms, Max time: 9.53254 ms, Average Time: 0.0830398 ms, Total: 12.504442 sec
// 100000P improved isPuzzleSolved  Min time: 0.078599 ms, Max time: 20.8862 ms, Average Time: 0.0918014 ms, Total: 13.866896 sec
// 10000P improved isPuzzleSolved   Min time: 0.074799 ms, Max time: 16.8161 ms, Average Time: 0.0856129 ms, Total: 1.291579 sec
// time for 10000P.txt -            Min time: 0.2968 ms, Max time: 1.1741 ms, Average Time: 0.468564 ms, Total: 8.292689 sec
// for 5000P.txt -       Min time: 0.3026 ms, Max time: 1.0865 ms, Average Time: 0.466454 ms, Total: 4.142156 sec

// mac release
//blank constructor
//parameter ../../../../SudokuPuzzles/5000P.txt
//5000 puzzles loaded
//Solved 5000 out of 5000 puzzles
//Min time: 0.111575 ms, Max time: 19.5198 ms, Average Time: 0.163679 ms, Total: 1.376686 sec
//Program ended with exit code: 0

// mac debug
//blank constructor
//parameter ../../../../SudokuPuzzles/5000P.txt
//5000 puzzles loaded
//Solved 5000 out of 5000 puzzles
//Min time: 0.466408 ms, Max time: 88.6324 ms, Average Time: 0.572413 ms, Total: 4.465807 sec
//Program ended with exit code: 0

// 	    1   2   3    4   5   6    7   8   9
//   =========================================
// A || . | 4 | 3 || . | 8 | . || 2 | 5 | . ||
// B || 6 | . | . || . | . | . || . | . | . ||
// C || . | . | . || . | . | 1 || . | 9 | 4 ||
//   || --------- || --------- || --------- ||
// D || 9 | . | . || . | . | 4 || . | 7 | . ||
// E || . | . | . || 6 | . | 8 || . | . | . ||
// F || . | 1 | . || 2 | . | . || . | . | 3 ||
//   || --------- || --------- || --------- ||
// G || 8 | 2 | . || 5 | . | . || . | . | . ||
// H || . | . | . || . | . | . || . | . | 5 ||
// I || . | 3 | 4 || . | 9 | . || 7 | 1 | . ||
//   =========================================

//      1   2   3    4   5   6    7   8   9
//   =========================================
// A || 1 | 4 | 3 || 9 | 8 | 6 || 2 | 5 | 7 ||
// B || 6 | 7 | 9 || 4 | 2 | 5 || 3 | 8 | 1 ||
// C || 2 | 8 | 5 || 7 | 3 | 1 || 6 | 9 | 4 ||
//   || --------- || --------- || --------- ||
// D || 9 | 6 | 2 || 3 | 5 | 4 || 1 | 7 | 8 ||
// E || 3 | 5 | 7 || 6 | 1 | 8 || 9 | 4 | 2 ||
// F || 4 | 1 | 8 || 2 | 7 | 9 || 5 | 6 | 3 ||
//   || --------- || --------- || --------- ||
// G || 8 | 2 | 1 || 5 | 6 | 7 || 4 | 3 | 9 ||
// H || 7 | 9 | 6 || 1 | 4 | 3 || 8 | 2 | 5 ||
// I || 5 | 3 | 4 || 8 | 9 | 2 || 7 | 1 | 6 ||
//   =========================================
// Puzzle 6, Solved = True, Time = 0.2327 ms


// solved with ones/peers
// grid1 = '003020600900305001001806400008102900700000008006708200002609500800203009005010300'
// grid3 = "802050701007082460010900000600001832500000009184300006000004020095610300308090607"


// not solved with ones/peers
// easy505 = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6"
// grid2 = '4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......'
// hard1 = '.....6....59.....82....8....45........3........6..3.54...325..6..................'
