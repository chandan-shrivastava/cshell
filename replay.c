#include "replay.h"

void replay()
{
	if (strcmp(command[1], "-command") != 0)
	{
		fprintf(stderr, "Error: Incorrect Usage\n");
		return;
	}
	int interval;
	int period;
	for (int i = 0; i < args; i++)
	{
		if (strcmp(command[i], "-interval") == 0)
		{
			interval = atoi(command[i + 1]);
			period = atoi(command[i + 3]);
			if (isdigit(interval) != 0 || strcmp(command[i + 2], "-period") != 0 || isdigit(period != 0))
			{
				fprintf(stderr, "Error: Incorrect Usage\n");
				return;
			}
		}
	}
	int nooftime = period / interval;
	char replaycmd[1000] = {};
	char replaycmd1[1000] = {};
	int cnt = 0;
	for (int i = 2; i < args; i++)
	{
		if (!strcmp(command[i], "-interval"))
		{
			break;
		}
		else
		{
			cnt++;
			strcat(replaycmd, command[i]);
			strcat(replaycmd, " ");
		}
	}
	for (int i = cnt; i < args; i++)
	{
		command[i] = "";
	}
	strcpy(replaycmd1, replaycmd);
	removewhitespaces(replaycmd);
	for (int i = 0; i < nooftime; i++)
	{
		sleep(interval);

		execute(replaycmd1);
	}
}