/*
 * TruthTable.cpp
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 *	Modified on: 17/05/2014
 *		Author: Calum
 */

#include "TruthTable.h"
#include <math.h>
#include <iostream>

TruthTable::TruthTable() {
	// TODO Auto-generated constructor stub

}

TruthTable::~TruthTable() {
	// TODO Auto-generated destructor stub
}

void TruthTable::run() 
{
	int numRules = allRules.size();

	//Go through all numbers from 0 to 2^x where x is the number of values in the truth table, and find if model of the "ASK"
	for (int i = 0; i < pow(2, numRules); i++)
	{
		int j = 0;
		//Set values
		for (auto rule : allRules)
		{
			if ((i & (1 << j)) != 0)
				rule.second->val = TRUE;
			else
				rule.second->val = FALSE;
			j++;
		}

		if (allRules["a"]->val == TRUE && allRules["b"]->val == TRUE && allRules["c"]->val == TRUE && allRules["d"]->val == TRUE && allRules["e"]->val == TRUE && allRules["f"]->val == TRUE && allRules["g"]->val == FALSE && allRules["p1"]->val == TRUE &&allRules["p2"]->val == TRUE &&allRules["p3"]->val == TRUE)
		{
			bool shouldBeTrue = true;
		}

		//Go through each rule and check if true with given values of variables
		bool isPartOfKnowledgeBase = true;
		for (auto currentRule : allRules)
		{
			if (!currentRule.second->isRule)
				continue;
			//If the selected inputs don't match the knowledge base for this rule, then break, as none of the knowledge base will match
			if (truthCheck(currentRule.second) == FALSE)
			{
				isPartOfKnowledgeBase = false;
				break;
			}
		}

		//If combination of values matches the knowledge base and the ASK is true, it is a model of the ASK, and so increment the count
		if (isPartOfKnowledgeBase)
		{
			if (allRules[target->name]->val == TRUE)
				modelsFound++;
			else
				impliedByKnowledgeBase = false;
		}
			
	}
}

void TruthTable::print() 
{
	if (impliedByKnowledgeBase)
		std::cout << "YES : " << modelsFound << std::endl;
	else
		std::cout << "NO : " << modelsFound << std::endl;
}

//Finds all rules related to the given rule
std::vector<rule *> *TruthTable::findRules(rule* parentRule)
{
	std::vector<rule *> *retVal = new std::vector<rule *>();
	//Find all rules associated with children of given rule
	if (parentRule->children.size() > 0)
	{
		for (rule *child : parentRule->children)
		{
			retVal->push_back(child);
			std::vector<rule *> *values = findRules(child);
			for (rule *value : *values)
			{
				retVal->push_back(value);
			}
		}
	}

	return retVal;
}

//Checks whether the current rule (with the current values) equates to true or false
value TruthTable::truthCheck(rule *toCheck)
{
	//IF there are no children the knowledge base requires it be true. If this is not the case return false as it doesn't match the knowledge base.
	if (toCheck->children.size() == 0)
	{
		if( toCheck->val == TRUE)
			return TRUE;
		else return FALSE;
	}

	//And all of the children (LHS of the implication) together, setting andedresult to the result
	bool andedResult = true;
	for (rule *child : toCheck->children)
	{
		if (child->val == FALSE)
		{
			andedResult = false;
			break;
		}
	}

	//Perform the implication using current values
	if (andedResult)
		return toCheck->val;
	else
		return TRUE;
}
