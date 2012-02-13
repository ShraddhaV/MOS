/*
 * mos.h
 *
 *  Created on: Jan 13, 2012
 *
 */
#ifndef MOS_H_
#define MOS_H_
#include "lineprinter.h"
#include "cpu.h"
#include "cardreader.h"
#include "stdlib.h"
class Cpu;
class MOS {
	char sys_ibuff[45],sys_obuff[45];
	Cpu *c;
	Memory *m;
	CardReader *cr;
	LinePrinter *pr;
	int curr_gid,curr_pid,iinstructions,ilines,itinstructions,itlines;
	vector<string> error[10];
	int NoOfErrors;
	vector<string> e = {"No Error","Out Of Data","Line Limit Exceeded","Time Limit Exceeded" ,"Operation Code Error","Operand Error","Invalid Page Fault"};
	// Please chck the syntax.. I dont know it.

	public :
	int gd_service(Cpu *c);//interrupt handlers for
	void pd_service(Cpu *c);//si=1,2,3 respectively
	void h_service(Cpu *c);
	void check(Cpu *c);
	static const int amj_card=0;
	static const int dta_card=amj_card+1;
	static const int end_card=dta_card+1;
	static const int prog_card=end_card+1;
	friend class Cpu;

	MOS();
	MOS(LinePrinter *lnpr, CardReader *crd){
		cr = crd;
		pr = lnpr;
	}
	virtual ~MOS();
};

#endif /* MOS_H_ */
