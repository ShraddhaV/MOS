//============================================================================
// Name        : mos.cpp
// Author      :
// Version     :
// Copyright   : GPL v3
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
using namespace std;
#include "mos.h"
#include "memory.h"
#include "cpu.h"
#include "lineprinter.h"
#include "cardreader.h"
int main() {
	Memory m;
	LinePrinter lnpr("outfile1.txt");
	CardReader crd("printout.txt");
	MOS os(&lnpr,&crd);
	Cpu c(&m,&os);
	while(1)
	{
		c.fetch();				// where will the real address get stored ?
		c.execute();			// execute chya adhi check thevla tar sr, lr, etc la lagnare flags pan check karata yetil
		os.check(&c);
	}
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	ifstream i("../");
	return 0;
}
