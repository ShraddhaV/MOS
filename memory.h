/*
 * memory.h
 *
 *  Created on: Jan 13, 2012
 *      Author: miheer
 */

#ifndef MEMORY_H_
#define MEMORY_H_

class Memory {
	int mm[100];
public:
	int read(int address);
	void write(int address,int data);
	Memory();
	virtual ~Memory();
};

#endif /* MEMORY_H_ */
