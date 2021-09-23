#include "headers.h"

#ifndef __HISTORY_H
#define __HISTORY_H

int prevhistory();
void writehistorytofile(char cmd[]);
void history();
int text_delete();
char *getlastline();

#endif