#include "fgbg.h"

void fgbg(int bgorfg)
{
	int j = 0;
	for (int i = 0; i < args; i++)
	{
		if (strcmp(command[i], ""))
		{
			command[j++] = command[i];
		}
	}
	command[j] = 0;
	pid_t fgbgpid;
	int pidstatus;
	fgbgpid = fork();
	if (fgbgpid < 0)
	{
		printf("Failed forking\n");
	}
	else if (!fgbgpid)
	{
		setpgid(0, 0);
		if (execvp(command[0], command) < 0)
		{
			printf("Error executing %s command\n", command[0]);
			exit(1);
		}
	}
	if (bgorfg)
	{
		char name[1024];
		strcpy(name, command[0]);
		for (int i = 1; i < j; i++)
		{
			strcat(name, " ");
			strcat(name, command[i]);
		}
		strcpy(pid1[fgbgpid], name);
		printf("%d\n", fgbgpid);
	}
	else
	{
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		tcsetpgrp(0, fgbgpid);
		waitpid(fgbgpid, &pidstatus, WUNTRACED);
		tcsetpgrp(0, shellpid);
	}
}
