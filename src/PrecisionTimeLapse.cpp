#include <iomanip>
#include <sstream>
using namespace std;
#include "PrecisionTimeLapse.h"  
	
PrecisionTimeLapse::PrecisionTimeLapse() {

}
void PrecisionTimeLapse::start() {
    begin = high_resolution_clock::now();
}

void PrecisionTimeLapse::stop() {
    end = high_resolution_clock::now();
}

double PrecisionTimeLapse::elapsed() {
    time_lapse = duration_cast<nanoseconds> (end - begin);
    return (double)time_lapse.count();
}

string PrecisionTimeLapse::elapsedString() {
    return elapsedString(MILLISEC);
}
string PrecisionTimeLapse::elapsedString(TIME_UNIT tu) {
    string retval;          // string which will contain the result
    // ostringstream convert;   // stream used for the conversion
    // convert << elapsed();      // insert the textual representation of 'Number' in the characters in the stream
    // retval = convert.str(); // set 'Result' to the contents of the stream
    // retval.
    retval = to_string(elapsed() * tu);
    return retval;
}