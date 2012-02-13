/*
 * cpu.h
 *  Created on: Jan 13, 2012
 */
#ifndef CPU_H_
#define CPU_H_
#include "memory.h"
#include"mos.h"
class MOS;
class Cpu {
	short ip;	//instruction pointer
	int acc;	//accumulator
	char c;		//c flag
	int ir;
	int si;
	int pi;
	int ti;
	int PTR;
	MOS *os;
	Memory *m;
	long clk;
	Cpu();
	class PMMU
	{
		int flag;
	public :
		PMMU()
		{
			flag = 0;
		}
		int Address_Map(int VirtualAddr)
		{
			if(m->read(PTR + int(VirtualAddr / 10)) == -1)
			{
				pi = 3;
			}
			else
			{
				if (m->read(PTR + (int)(VirtualAddr/10))  < 0 || m->read(PTR + (int)(VirtualAddr/10)) >= 300)		// please check this later
				{
					// Its given that its a page fault.. Shouldnt it be an operand error.
					pi = 2;
				}
				else
				{
					return(m-read(PTR + (int)(VirtualAddr/10)));
				}
			}

		}
		int Allocate()
		{
			while(flag != 1)
			{
				int page_no = rand() % 30;			// This will generate a random number between 0 to 29
				// check if that pageno is already used. If so, continue..
				//else ,, flag = 1 and perform the following for loop
				for(int i = 0;i < 10;i++)
				{
					this->m->write((page_no * 10 + i) , (-1));
				}
			}
			flag = 0;
			return(page_no);
		}
	};
public:
	Cpu(Memory *mm,MOS *os);
	void fetch();
	void decode();
	void execute();
	static const int gd=0;
	static const int pd=1;
	static const int lr=2;
	static const int sr=3;
	static const int cr=4;
	static const int bt=5;
	static const int h=6;
	friend class MOS;
	virtual ~Cpu();
};

#endif /* CPU_H_ */
