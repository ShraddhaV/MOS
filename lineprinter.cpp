#include "lineprinter.h"
LinePrinter::LinePrinter() {

}
LinePrinter::LinePrinter(const char *ofile){
	outfilename=ofile;
	f=new ofstream(ofile);
}
void LinePrinter::print(char* buff){
	for(int i=0;buff[i] && i<40;i++){
		f->put(buff[i]);
	}
	(*f)<<"\n";
}
LinePrinter::~LinePrinter() {
	if(f)
	{
		f->flush();
		f->close();
		delete f;
	}
}
