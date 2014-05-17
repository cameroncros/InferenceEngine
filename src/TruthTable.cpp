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
	//Get a list of rules to put through the truth table
	std::vector<rule *> *discoveredRules = findRules(target);

	int numRules = discoveredRules->size();

	//Set the value of the target to true to ensure we only return results matching the "ASK"
	std::map<std::string, value> valueMap;
	valueMap[target->name] = TRUE;

	discoveredRules->push_back(target);

	//Go through all numbers from 0 to 2^x where x is the number of values in the truth table, and find if model of the "ASK"
	for (int i = 0; i < pow(2, numRules); i++)
	{
		//Convert to map representing row of truth table
		for (int j = 0; j < numRules; j++)
		{
			if ((i & (1 << j)) != 0)
				valueMap[discoveredRules->at(j)->name] = TRUE;
			else
				valueMap[discoveredRules->at(j)->name] = FALSE;
		}

		//Go through each rule and check if true with given values of variables
		bool isModel = true;
		for (rule *currentRule : *discoveredRules)
		{
			//Set the values in the 'rule' variables from the mappings
			currentRule->val = valueMap[currentRule->name];
			for (rule *child : currentRule->children)
			{
				child->val = valueMap[child->name];
			}

			//If one element of the KB is false it's not a model, so don't check the rest
			if (truthCheck(currentRule) == FALSE)
			{
				isModel = false;
				break;
			}
		}

		//Increment models found count
		if (isModel)
			modelsFound++;
	}
}

void TruthTable::print() 
{
	if (modelsFound > 0)
		std::cout << "YES " << modelsFound;
	else
		std::cout << "NO 0";
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
	//And all of the children (LHS of the implication) together, setting andedresult to the result
	bool andedResult = true;
	for (rule *child : toCheck->children)
	{
		if (child->val == FALSE)
		{
			andedResult = true;
			break;
		}
	}

	//Perform the implication using current values
	if (!andedResult || toCheck->val == TRUE)
		return TRUE;
	else
		return FALSE;
}