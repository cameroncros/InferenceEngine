/*
 * TruthTable.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef TRUTHTABLE_H_
#define TRUTHTABLE_H_

#include "Engine.h"
#include "KnowledgeBase.h"

class TruthTable: public Engine {
public:
	TruthTable(KnowledgeBase *kb);
	virtual ~TruthTable();

	void run();
	void print();
};

#endif /* TRUTHTABLE_H_ */
