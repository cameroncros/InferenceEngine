/*
 * ForwardChaining.cpp
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 *	Modified on: 24/05/2014
 *		Author: Calum
 */

#include "ForwardChaining.h"
#include <iostream>
#include <algorithm>

ForwardChaining::ForwardChaining() {
	found = false;
	// TODO Auto-generated constructor stub

}

ForwardChaining::~ForwardChaining() {
	// TODO Auto-generated destructor stub
}

void ForwardChaining::run()
{
	//Add all symbols initially known to be true
	for (auto rule : allRules)
	{
		if (rule.second->val == TRUE)
			agenda->push_back(rule.second);
	}

	while (!agenda->empty())
	{
		//Process the next rule
		rule *rl = agenda->front();
		agenda->pop_front();


		if (checkRule(rl)==TRUE) {
			rl->val = TRUE;
		} else {
			continue;
		}

		//Add to list of symbols found
		searchedRules->push_back(rl);



		//Check if solution
		if (rl->name == target->name)
		{
			found = true;
			return;
		}

		//Cycle through each horn claus and add each with rule in the premise to the agenda
		for (auto nextRule : allRules)
		{
			for (rule *child : nextRule.second->children)
			{
				if (child->name != rl->name)
				{
					continue;
				}
				//If we haven't already searched the rule add it to the agenda
				if (notInVector(searchedRules, nextRule.second) == true)
				{
					agenda->push_back(nextRule.second);
					break;
				}

			}
		}
	}
}

void ForwardChaining::print()
{
	if (found == true) {
		std::cout << "YES: ";
		for (rule *rl : *searchedRules) {
			std::cout << rl->name << ", ";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}

bool ForwardChaining::notInVector(std::vector<rule *> *vect, rule *child)
{
	return (std::find(vect->begin(), vect->end(), child) == vect->end());
}
