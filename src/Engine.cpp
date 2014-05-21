/*
 * Engine.cpp
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#include "Engine.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

Engine::Engine() {
	target = NULL;
	filename = NULL;
	// TODO Auto-generated constructor stub

}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

void Engine::load(const char *filestr) {
	std::string filename(filestr);
	std::string string;
	std::ifstream file(filename, std::ios_base::in);
	if (!file.is_open()) {
		std::cout << "Failed to open files" << std::endl;
		exit(-1);
	}

	std::getline(file, string);
	removeLineEndings(string);
	if (string.compare("TELL") != 0) {
		std::cout << "File seems to be invalid" << std::endl;
		exit(-1);
	}

	std::getline(file, string);
	removeLineEndings(string);
	replace(string, " ", "");
	replace(string, "=>", "&");
	std::vector<std::string> *rulelist = split(string, ";");
	for (std::string rulestr : *rulelist) {
		if (rulestr.length() == 0) {
			continue;
		}
		std::vector<std::string> *parts = split(rulestr, "&");
		int numRules = parts->size();
		for (std::string newnode : *parts) {
			if (allRules.find(newnode) == allRules.end()) {
				rule *temp = new rule;
				temp->name = newnode;
				temp->val = UNDEFINED;
				temp->isRule = false;
				allRules.insert(std::pair<std::string, rule *>(temp->name, temp));
			}
		}
		rule *temp = allRules[(*parts)[numRules-1]];
		if (numRules == 1) {
			temp->val=TRUE;
		} else {
			temp->val=UNDEFINED;
			for (int i=0; i < (numRules-1); i++) {
				temp->children.push_back(allRules[(*parts)[i]]);
			}
		}
		temp->isRule = true;
	}


	std::getline(file, string);
	removeLineEndings(string);
	if (string.compare("ASK") != 0) {
		std::cout << "File seems to be invalid" << std::endl;
		exit(-1);
	}

	std::getline(file, string);
	removeLineEndings(string);
	target = allRules[string];

}

void Engine::replace(std::string &str, const char *from, const char *to) {
	size_t pos;
	std::string fromString(from);
	std::string toString(to);
	while ((pos = str.find(from, 0)) != std::string::npos) {
		str.erase(pos, fromString.length());
		str.insert(pos, toString);
	}
}

//this is needed to remove stray \n and \r that popup on other platforms (linux)
void Engine::removeLineEndings(std::string &str) {
	replace(str, "\n", "");
	replace(str, "\r", "");
}	

std::vector<std::string> *Engine::split(std::string &str, const char *val) {
	std::string value(val);
	std::vector<std::string> *parts = new std::vector<std::string>();
	size_t pos, last_pos = 0;
	while ((pos = str.find(value, last_pos)) != std::string::npos) {
		parts->push_back(str.substr(last_pos, pos-last_pos));
		last_pos = pos + value.length();
	}
	parts->push_back(str.substr(last_pos));


	return parts;

}

void Engine::printKnowledgeBase() {
	for (auto i = allRules.begin(); i != allRules.end(); i++) {
		rule *temp = (*i).second;
		int numChildren = temp->children.size();
		for (int i = 0; i < numChildren-1; i++) {
			std::cout << temp->children[i]->name << " AND ";
		}


		if (numChildren != 0) {
			std::cout << temp->children[numChildren-1]->name << " IMPLYS " << temp->name << std::endl;
		} else {
			switch (temp->val) {
			case TRUE:
				std::cout << temp->name << " EQUALS TRUE" << std::endl;
				break;
			case FALSE:
				std::cout << temp->name << " EQUALS FALSE" << std::endl;
				break;
			case UNDEFINED:
				std::cout << temp->name << " EQUALS UNKNOWN" << std::endl;
				break;
			}
		}
	}

	std::cout << "ASKED FOR " << target->name << std::endl;

}

value Engine::checkRule(rule *rl) {
	if (rl->val == TRUE) {
		return TRUE;
	}
	if (rl->children.size() == 0 ) {
		return rl->val;
	}
	for (rule *l : rl->children) {
		switch (l->val) {
		case TRUE:
			continue;
		default:
			return l->val;

		}
	}
	return TRUE;
}
