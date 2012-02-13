/*
 * lineprinter.h
 *
 *  Created on: Jan 13, 2012
 *      Author: miheer
 */

#ifndef LINEPRINTER_H_
#define LINEPRINTER_H_
#include <fstream>
#include <string>
using std::string;
using std::ofstream;
class LinePrinter {
	ofstream *f;
	string outfilename;
	LinePrinter();
public:
	LinePrinter(const char* ofile);
	void print(char *buffer);
	void printBL(int);
	virtual ~LinePrinter();
};

#endif /* LINEPRINTER_H_ */
