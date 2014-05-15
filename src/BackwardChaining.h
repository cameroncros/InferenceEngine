/*
 * BackwardChaining.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef BACKWARDCHAINING_H_
#define BACKWARDCHAINING_H_

#include "Engine.h"

class BackwardChaining: public Engine {
public:
	BackwardChaining();
	virtual ~BackwardChaining();

	void run();
	void print();
};

#endif /* BACKWARDCHAINING_H_ */
