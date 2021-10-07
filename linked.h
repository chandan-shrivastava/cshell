#include "headers.h"
#ifndef _LINKED_H_
#define _LINKED_H_

struct Node *newjob(struct Node *headptr, pid_t pid, char name[], int jnum);
struct Node *deletejob(struct Node *head, pid_t pid);
char *findnamebypid(struct Node *head, pid_t pid);
pid_t findpidbyjobno(struct Node *head, int job);
void bubbleSort(struct Node *start);
void swap(struct Node *a, struct Node *b);

#endif