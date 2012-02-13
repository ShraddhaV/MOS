/*
 * cardreader.h
 *
 *  Created on: Jan 13, 2012
 *      Author: miheer
 */

#ifndef CARDREADER_H_
#define CARDREADER_H_
#include <string>
#include <fstream>
using std::ifstream;
using std::string;
class CardReader {
	string infilename;
	ifstream *f;
	CardReader();
public:
	CardReader(const char* ifile);
	int read(char* buffer);
	static const int out_of_cards=-1;
	virtual ~CardReader();
};

#endif /* CARDREADER_H_ */
