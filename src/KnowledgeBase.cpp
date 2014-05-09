/*
 * KnowledgeBase.cpp
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#include "KnowledgeBase.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

KnowledgeBase::KnowledgeBase(const char *file) {
	filename = file;
	target = NULL;
	load();
}

KnowledgeBase::~KnowledgeBase() {

	// TODO Auto-generated destructor stub
}

void KnowledgeBase::load() {
	std::string string;
	std::ifstream file(filename, std::ios_base::in);
	if (!file.is_open()) {
		std::cout << "Failed to open files" << std::endl;
		exit(-1);
	}

	std::getline(file, string);
	if (string.compare("TELL") != 0) {
		std::cout << "File seems to be invalid" << std::endl;
		exit(-1);
	}

	std::getline(file, string);
	replace(string, " ", "");
	replace(string, "=>", "&");
	std::vector<std::string> *rulelist = split(string, ";");
	for (std::string rulestr : *rulelist) {
		std::vector<std::string> *parts = split(rulestr, "&");
		for (std::string newnode : *parts) {
			if (allRules.find(newnode) == allRules.end()) {
				rule *temp = new rule;
				temp->name = newnode;
				allRules.insert(std::pair<std::string, rule *>(temp->name, temp));
			}
		}
		rule *temp = allRules[(*parts)[parts->size()-1]];
		switch (parts->size()) {
		case 1:
			temp->val=TRUE;
			break;
		case 2:
			temp->children.push_back(allRules[(*parts)[0]]);
			break;
		case 3:
			temp->children.push_back(allRules[(*parts)[0]]);
			temp->children.push_back(allRules[(*parts)[1]]);
			break;
		}

	}


	std::getline(file, string);
	if (string.compare("ASK") != 0) {
		std::cout << "File seems to be invalid" << std::endl;
		exit(-1);
	}

	std::getline(file, string);
	target = allRules[string];

	std::cout << string << std::endl;
}

void KnowledgeBase::replace(std::string &str, const char *from, const char *to) {
	size_t pos;
	std::string fromString(from);
	std::string toString(to);
	while ((pos = str.find(from, 0)) != std::string::npos) {
		str.erase(pos, fromString.length());
		str.insert(pos, toString);
	}
}

std::vector<std::string> *KnowledgeBase::split(std::string &str, const char *val) {
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

void KnowledgeBase::printKnowledgeBase() {
	for (auto i = allRules.begin(); i != allRules.end(); i++) {
		rule *temp = (*i).second;
		switch (temp->children.size()) {
		case 0:
			std::cout << temp->name << std::endl;
			continue;
		case 1:
			std::cout << temp->children[0]->name;
			break;
		case 2:
			std::cout << temp->children[0]->name << " AND " << temp->children[1]->name;
			break;
		default:
			std::cout << "Something went wrong" << std::endl;
		}
		std::cout << " IMPLYS " << temp->name << std::endl;
	}
}

