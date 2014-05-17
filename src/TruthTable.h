/*
 * TruthTable.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 *	Modified on: 17/05/2014
 *		Author: Calum
 */

#ifndef TRUTHTABLE_H_
#define TRUTHTABLE_H_

#include "Engine.h"

class TruthTable: public Engine {
private:
	int modelsFound = 0;

	std::vector<rule *> *findRules(rule* parentRule);
	value truthCheck(rule *toCheck);
public:
	TruthTable();
	virtual ~TruthTable();

	void run();
	void print();
};

#endif /* TRUTHTABLE_H_ */
