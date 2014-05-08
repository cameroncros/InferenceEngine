/*
 * KnowledgeBase.h
 *
 *  Created on: 08/05/2014
 *      Author: Cameron
 */

#ifndef KNOWLEDGEBASE_H_
#define KNOWLEDGEBASE_H_

class KnowledgeBase {
private:
	typedef struct node {


	} node;

public:
	KnowledgeBase(const char *file);
	virtual ~KnowledgeBase();

	void load(const char *filename);
};

#endif /* KNOWLEDGEBASE_H_ */
