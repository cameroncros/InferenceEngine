/*
 * BackwardChaining.cpp
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#include "BackwardChaining.h"
#include <vector>
#include <iostream>
#include <algorithm>

BackwardChaining::BackwardChaining() {
	found = true;
}

BackwardChaining::~BackwardChaining() {
	// TODO Auto-generated destructor stub
}

void BackwardChaining::run() {
	int noChangeCount = 0;
	discoveredRules->push_back(this->target);
	while (discoveredRules->size() != 0) {
		for (unsigned int i = 0; i < discoveredRules->size(); i++) {
			rule *rl = (*discoveredRules)[i];
			if (checkRule(rl) == TRUE) {
				rl->val=TRUE;
				for (rule *child : rl->children) {
					if (notInVector(confirmedRules, child) == true) {
						confirmedRules->push_back(child);
						noChangeCount = 0;
					}
				}
			} else {
				for (rule *child : rl->children) {
					if (notInVector(discoveredRules, child) == true) {
						discoveredRules->push_back(child);
						noChangeCount = 0;
					}
				}
			}
			if (rl == target && checkRule(rl)==TRUE) {
				confirmedRules->push_back(rl);
				found = true;
				return;
			}
			if (noChangeCount == 3) { //checks if there has been any progress
				found = false;
				return;
			}
			noChangeCount++;
		}
	}

}

void BackwardChaining::print() {
	if (found == true) {
	std::cout << "YES: ";
	for (rule *rl : *confirmedRules) {
		std::cout << rl->name << ", ";
	}
	std::cout << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
}

bool BackwardChaining::notInVector(std::vector<rule *> *vect, rule *child) {
	return (std::find(vect->begin(), vect->end(), child) == vect->end());

}
