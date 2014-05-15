#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "KnowledgeBase.h"
#include "TruthTable.h"
#include "ForwardChaining.h"
#include "BackwardChaining.h"



int main(int argc, char **argv) {
	KnowledgeBase *kb = NULL;
	enginetype method;
	Engine *search = NULL;
	if (!(argc == 3)) {
		printusage(argv[0]);
	}
	method = getSearchType(argv[2]);
	if (method == INVALID) {
		printusage(argv[0]);
	}
	kb = new KnowledgeBase(argv[1]);
	kb->printKnowledgeBase();
	switch (method) {
	case TT:
		//Calum
		search = new TruthTable(kb);
		break;
	case FC:
		//Vinayak
		search = new ForwardChaining(kb);
		break;
	case BC:
		//Cameron
		search = new BackwardChaining(kb);
		break;
	case INVALID:
		search = NULL;
		break;
	}
	if (search != NULL) {
		search->run();
		search->print();
		delete(search);
	}
	else {
		printusage(argv[0]);
	}
	return 0;
}



enginetype getSearchType(char *methodstr) {

	if (strncmp("TT", methodstr, 3) == 0) {
		return TT;
	}
	if (strncmp("tt", methodstr, 3) == 0) {
		return TT;
	}
	if (strncmp("FC", methodstr, 3) == 0) {
		return FC;
	}
	if (strncmp("fc", methodstr, 3) == 0) {
		return FC;
	}
	if (strncmp("BC", methodstr, 4) == 0) {
		return BC;
	}
	if (strncmp("bc", methodstr, 4) == 0) {
		return BC;
	}
	return INVALID;
}

void printusage(char *progname) {
	printf("Usage: %s [filename] [method] \n\n"
			"Methods:\n"
			"TT: Truth Table\n"
			"FC: Forward Chaining\n"
			"BC: Backward Chaining\n", progname);
	exit(1);
}



