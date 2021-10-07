#include "jobs.h"

void jobs()
{
	struct Node *temp = head;
	bubbleSort(temp);
	while (temp != NULL)
	{
		pid_t pid = temp->pid;
		int jnum = temp->job;
		char *name = temp->name;
		char status[10];
		char path[1024];
		sprintf(path, "/proc/%d/status", pid);
		char *line = NULL;
		size_t len = 0, read;

		FILE *fp = fopen(path, "r");
		if (fp == NULL)
		{
			fprintf(stderr,"Error opening %s file\n", path);
		}
		else
		{
			int line_no = 0;
			while ((read = getline(&line, &len, fp)) != -1)
			{
				line_no++;
				if (line_no == 3)
				{
					char *token = strtok(line, " \t");
					token = strtok(NULL, " \t");
					if (!strcmp(token, "S") || !strcmp(token, "D") || !strcmp(token, "R"))
						strcpy(status, "Running");
					else
						strcpy(status, "Stopped");
					break;
				}
			}
			fclose(fp);
			if (args > 1 && !strcmp(command[1], "-r") && !strcmp(status, "Running"))
			{
				printf("[%d] %s %s [%d]\n", jnum, status, name, pid);
			}
			else if (args > 1 && !strcmp(command[1], "-s") && !strcmp(status, "Stopped"))
			{
				printf("[%d] %s %s [%d]\n", jnum, status, name, pid);
			}
			else if (args == 1)
			{
				printf("[%d] %s %s [%d]\n", jnum, status, name, pid);
			}
		}
		temp = temp->next;
	}
}
