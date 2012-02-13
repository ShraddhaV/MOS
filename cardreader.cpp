/*
 * cardreader.cpp
 *
 *  Created on: Jan 13, 2012
 */

#include "cardreader.h"

CardReader::CardReader() {


}
CardReader::CardReader(const char* ifile){
	infilename=ifile;
	f=new ifstream(ifile);
}
CardReader::~CardReader() {
	if(f){
		f->close();
		delete f;
	}
}
int CardReader :: read(char* buff)
{
	if(f->eof())
	{
		return out_of_cards;
	}
	f->getline(buff,41,'\n');
	return out_of_cards+1;
}
