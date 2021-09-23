#include "headers.h"

#ifndef __LS_H
#define __LS_H

void ls();
void lsfull(char filepath[], char *file);
void lspath(char path[], int full, int hide);
int checkmorethan6month(int mon1, int day1, int year1, int mon2, int day2, int year2);

#endif