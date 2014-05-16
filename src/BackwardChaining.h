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
private:
	std::vector<rule *> *discoveredRules = new std::vector<rule *>();
	std::vector<rule *> *confirmedRules = new std::vector<rule *>();
	bool found;
public:
	BackwardChaining();
	virtual ~BackwardChaining();

	void run();
	void print();

	bool notInVector(std::vector<rule *> *vect, rule *child);
};

#endif /* BACKWARDCHAINING_H_ */
