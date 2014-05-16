/*
 * Engine.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef ENGINE_H_
#define ENGINE_H_

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

class Engine {
private:
	void replace(std::string &str, const char *from, const char *to);
	std::vector<std::string> *split(std::string &str, const char *val);

public:
	const char *filename;
	std::map<std::string, rule*> allRules;
	rule *target;

	Engine();
	virtual ~Engine();

	virtual void run()=0;
	virtual void print()=0;

	void load(const char *file);
	void printKnowledgeBase();

	value checkRule(rule *);
};

#endif /* ENGINE_H_ */
