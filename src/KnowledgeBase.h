/*
 * KnowledgeBase.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef KNOWLEDGEBASE_H_
#define KNOWLEDGEBASE_H_

#include <map>
#include <string>
#include <vector>

typedef enum value {
	TRUE,
	FALSE,
	UNDEFINED
} value;

typedef struct rule {
	std::string name;
	std::vector<rule *> children;
	value val;

} rule;

class KnowledgeBase {
private:
	const char *filename;
	std::map<std::string, rule*> allRules;
	rule *target;

	void replace(std::string &str, const char *from, const char *to);
	std::vector<std::string> *split(std::string &str, const char *val);


public:
	KnowledgeBase(const char *file);
	virtual ~KnowledgeBase();

	void load();
	void printKnowledgeBase();
};

#endif /* KNOWLEDGEBASE_H_ */
