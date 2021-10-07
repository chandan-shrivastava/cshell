#include "linked.h"

void swap(struct Node *a, struct Node *b)
{
	int temp = a->pid;
	a->pid = b->pid;
	b->pid = temp;

	int temp2 = a->job;
	a->job = b->job;
	b->job = temp2;

	char temp1[1000];
	strcpy(temp1, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp1);
}

void bubbleSort(struct Node *start)
{
	int swapped, i;
	struct Node *ptr1;
	struct Node *lptr = NULL;
	if (start == NULL)
		return;
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			int abc = ptr1->name[0];
			int abcd = ptr1->next->name[0];
			if (abc > abcd)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

struct Node *newjob(struct Node *head, pid_t pid, char name[], int jnum)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	struct Node *last = head;

	new_node->pid = pid;
	strcpy(new_node->name, name);
	new_node->job = jnum;
	new_node->next = NULL;

	if (!head)
	{
		head = new_node;
		return head;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	return head;
}

struct Node *deletejob(struct Node *head, pid_t pid)
{
	struct Node *temp = head;
	struct Node *last = head;

	if (temp && temp->pid == pid)
	{
		last = temp->next;
		free(temp);
		return last;
	}

	while (temp && temp->pid != pid)
	{
		last = temp;
		temp = temp->next;
	}

	last->next = temp->next;
	free(temp);
	return head;
}

char *findnamebypid(struct Node *head, pid_t pid)
{
	if (!head)
		return NULL;

	struct Node *temp = head;

	while (temp && temp->pid != pid)
		temp = temp->next;

	if (!temp)
		return NULL;

	return temp->name;
}

pid_t findpidbyjobno(struct Node *head, int job)
{
	if (!head)
		return 0;

	struct Node *temp = head;

	while (temp && temp->job != job)
		temp = temp->next;

	if (!temp)
		return 0;

	return temp->pid;
}
