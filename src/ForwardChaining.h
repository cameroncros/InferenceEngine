/*
 * ForwardChaining.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef FORWARDCHAINING_H_
#define FORWARDCHAINING_H_

#include "Engine.h"
#include "KnowledgeBase.h"

class ForwardChaining: public Engine {
public:
	ForwardChaining(KnowledgeBase *kb);
	virtual ~ForwardChaining();

	void run();
	void print();
};

#endif /* FORWARDCHAINING_H_ */
