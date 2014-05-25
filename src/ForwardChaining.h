/*
 * ForwardChaining.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 *	Modified on: 24/05/2014
 *		Author: Calum
 */

#ifndef FORWARDCHAINING_H_
#define FORWARDCHAINING_H_

#include "Engine.h"
#include <list>

class ForwardChaining: public Engine {
private:
	std::list<rule *> *agenda = new std::list<rule *>();
	std::vector<rule *> *searchedRules = new std::vector<rule *>();
	bool found;
public:
	ForwardChaining();
	virtual ~ForwardChaining();

	void run();
	void print();

	bool notInVector(std::vector<rule *> *vect, rule *child);
};

#endif /* FORWARDCHAINING_H_ */
