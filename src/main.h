#ifndef MAIN_H
#define MAIN_H

#include <string>

enum enginetype {
	TT,
	FC,
	BC,
	INVALID
};

void printusage(char *progname);
enginetype getSearchType(char *methodstr);
void loadFile(char *filename);

#endif
