/*
 * mos.cpp
 *
 *  Created on: Jan 13, 2012
 */
#include "mos.h"

MOS::MOS() {

// create the page table and store its base address in the PTR
	NoOfErrors = -1;
	for(int i =0;i<10;i++)
	{
		error[i] = null;
	}
	int page_no = rand() % 30;			// This will generate a random number between 0 to 29
	this->c->PTR = page_no * 10;
	for(int i = 0;i < 10;i++)
	{
			this->m->write((page_no * 10 + i) , (-1));
	}
}
MOS::~MOS() {

}
void MOS::check(Cpu *c){
	this->c=c;
	this->m=c->m;
	iinstructions++;
	if(iinstructions>itinstructions)
	{	// this halt_service call not considered while printing 2 blank lines after the output of a job card
		// print 2 blank lines to the output file
		//  TI = 2;
		h_service(c);
	}
	if(!c->si)
	{
		return;
	}
	// all combinations of si,pi and ti can be checked here.. only if pi becomes 3 in GD while loading program cards .. It cannot be detected

	if(c->ti == 0 && c->si == 1)
	{
		gd_service(c);
	}
	else if(c->ti == 0 && c->si == 2)
	{
		pd_service(c);
	}
	else if(c->ti == 0 && c->si == 3)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[0];
		h_service(c);
	}
	else if(c->ti == 2 && c->si == 1)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[3];
		h_service(c);
	}
	else if(c->ti == 2 && c->si == 2)
	{
		pd_service(c);
		NoOfErrors++;
		error[NoOfErrors] = e[3];
		h_service(c);
	}
	else if(c->ti == 2 && c->si == 3)
	{
		h_service(c);
	}
	else if(c->ti == 0 && c->pi == 1)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[4];
		h_service(c);
	}
	else if(c->ti == 0 && c->pi == 2)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[5];
		h_service(c);

	}
	else if(c->ti == 0 && c->pi == 3)
	{
		if((((char*)&(this->c->ir))[0] =='G' && ((char*)&(this->c->ir))[1] =='D') || (((char*)&(this->c->ir))[0] =='S' && ((char*)&(this->c->ir))[1] =='R'))
		{
				// Check the syntax
				int base = this->c->MMUInstance.Allocate();
				this->c->ir = base;
				gd_service(c);
		}
		else
		{
			NoOfErrors++;
			error[NoOfErrors] = e[6];
			h_service(c);
		}

	}
	else if(c->ti == 2 && c->pi == 1)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[3];
		NoOfErrors++;
		error[NoOfErrors] = e[4];
		h_service(c);
	}
	else if(c->ti == 2 && c->pi == 2)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[3];
		NoOfErrors++;
		error[NoOfErrors] = e[5];
		h_service(c);
	}
	else if(c->ti == 2 && c->pi == 3)
	{
		NoOfErrors++;
		error[NoOfErrors] = e[3];
		h_service(c);
	}
}
// Page Table Pointer will be declared in the mos.h
/*Allocate(int r)
 {
	for(int i = 0 ; i < 10 ; i++)
	{
		mm.initialize(parameters);
	}
 }
 */
int MOS::gd_service(Cpu *c){
	(c->si)=0;
	if((cr->read(sys_ibuff))==cr->out_of_cards)
	{
		pr->~LinePrinter();
		cr->~CardReader();
		exit(0);
	}
	((char *)(&c->ir))[3]='0';
	if(sys_ibuff[0] == '$' && sys_ibuff[1] == 'A' && sys_ibuff[2] == 'M' && sys_ibuff[3] == 'J'){

		curr_gid=(sys_ibuff[4]-'0')*10+(sys_ibuff[5]-'0');
		curr_pid=(sys_ibuff[6]-'0')*10+(sys_ibuff[7]-'0');
		itinstructions=(sys_ibuff[8]-'0')*1000+(sys_ibuff[9]-'0')*100+(sys_ibuff[10]-'0')*10+(sys_ibuff[11]-'0');
		itlines=(sys_ibuff[12]-'0')*1000+(sys_ibuff[13]-'0')*100+(sys_ibuff[14]-'0')*10+(sys_ibuff[15]-'0');
		//	Should the page table be generated here ??
		return amj_card;
	}
	else if(sys_ibuff[0] == '$' && sys_ibuff[1] == 'D' && sys_ibuff[2] == 'T' && sys_ibuff[3] == 'A')
	{
		return dta_card;
	}
	else if(sys_ibuff[0] == '$' && sys_ibuff[1] == 'E' && sys_ibuff[2] == 'N' && sys_ibuff[3] == 'D')
	{
		int itgid=(sys_ibuff[4]-'0')*10+(sys_ibuff[5]-'0');
		int itpid=(sys_ibuff[6]-'0')*10+(sys_ibuff[7]-'0');
		if(itgid==curr_gid && itpid==curr_pid){
			//this code has no right to call halt_service let that be decide by halt_service
			//h_service(c);
		}
		return end_card;
	}
	else{
		int base;
		//check the address of the block in page table...
		if(  ((*mm[c->PTR + (((char*)(c->ir)[2]) - '0') * 10 + (((char*)(c->ir)[3]) - '0')])) == -1 )
		{
			pi = 3;
			base = (this->c->MMUInstance.Allocate()) * 10;
		}
		// if invalid page,,,, set PI = 3

		/*
			if(PI == 3 && TI == 2)
			{
				halt_service(Time Limit Exceeded)
			}
			else if(PI == 3)				We have to create a separate handler for PI = 3 or inside this GD ?
			{								if PI sets to 3 inside LR or
				r = random no;
				Allocate(r);
			}
		*/
		// tempbase = calculate random number
		//base = tempbase * 10
		//int base=((((char *)(&(c->ir)))[2])-'0')*10 + (((((char *)(&c->ir))[3]))-'0');
		for(int i=0;i<10;i++)
		{
			m->write((base + i),((int*)(sys_ibuff))[i]);
		}
		//Page Table[PTR + prg_card_no][0] = prg_cardno
		//Page Table[PTR + prg_card_no][1] = tempbase
		return prog_card;
	}
}
void MOS::pd_service(Cpu *c)
{
	(c->si)=0;
	ilines++;
	if(ilines>itlines)
		h_service(c);
	int base=((((char *)(&(c->ir)))[2])-'0')*10 + (((((char *)(&c->ir))[3]))-'0');
	int i=0;
	for(int x=0;x<10;x++)
	{
		int tempdata=(m->read(base + x));
		sys_obuff[i] = ((char*)(&tempdata))[0];
		i++;
		sys_obuff[i] = ((char*)(&tempdata))[1];
		i++;
		sys_obuff[i] = ((char*)(&tempdata))[2];
		i++;
		sys_obuff[i] = ((char*)(&tempdata))[3];
		i++;
	}
	pr->print(sys_obuff);
}
void MOS::h_service(Cpu *c)
{
	c->si=0;
	if(((char*)(&c->ir))[0]!=0)
	{
		//if h_service wasn't called first time
		//verify condition as it fails in case of less no of data cards
		//cpu has encountered atleast 1 halt instruction now we are ignoring
		//remaining data cards
		sys_obuff[0] = 0;
		pr->print(sys_obuff);
		while(gd_service(c)!=end_card);
	}
	//next card is either amj or our os may power off
	int card;
	while((card=gd_service(c))!=amj_card); //this will cause power off
	int i=0;
	((char*)&c->ir)[2]=i+'0';
	((char*)&c->ir)[3]=0+'0';
	while((card=gd_service(c))!=dta_card){
		i++;
		((char*)&c->ir)[2]=i+'0';
		((char*)&c->ir)[3]=0+'0';
	}
	if(card==dta_card)
	{
		c->ir=0;
		c->ip=0;
		c->acc=0;
		c->c=0;
		c->si=0;
		ilines=0;
		iinstructions=0;
		return;
	}
	// read next card.... if it is the '$end' card,,, halt
	// else if its an AMJ card,,, load the next instructions in the memory unless you get the $DTA card.
	// when you get the $DTA card stop ,,,,, and return
}
