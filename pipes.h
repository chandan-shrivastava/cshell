#include "headers.h"

#ifndef _PIPES_H_
#define _PIPES_H_

void execpipe(char cmd[]);
int separate(char str[], char *pipeCommands[32]);

#endif