#include "replay.h"

void replay()
{
	int interval;
	int period;
	for (int i = 0; i < args; i++)
	{
		if (strcmp(command[i], "-interval") == 0)
		{
			interval = atoi(command[i + 1]);
		}
		if (strcmp(command[i], "-period") == 0)
		{
			period = atoi(command[i + 1]);
		}
	}
	int nooftime = period / interval;
	char replaycmd[1000] = {};
	char replaycmd1[1000] = {};
	int cnt = 0;
	for (int i = 1; i < args; i++)
	{
		if (!strcmp(command[i], "-command"))
		{
			;
		}
		else if (!strcmp(command[i], "-interval"))
		{
			i++;
		}
		else if (!strcmp(command[i], "-period"))
		{
			i++;
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