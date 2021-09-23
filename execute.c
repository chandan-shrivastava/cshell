#include "execute.h"

void execute()
{
	if (command[0] != NULL)
	{
		int bg = 0;
		for (int i = 0; i < args; i++)
		{
			if (!strcmp(command[i], "&"))
			{
				bg = 1;
				command[i] = "";
				break;
			}
		}
		if (!strcmp(command[0], "quit"))
		{
			exit(0);
		}
		else if (!strcmp(command[0], "cd"))
		{
			if (args > 2)
			{
				fprintf(stderr, "Too many arguments!\n");
				return;
			}
			cd();
		}
		else if (!strcmp(command[0], "pwd"))
		{
			pwd();
		}
		else if (!strcmp(command[0], "echo"))
		{
			echo();
		}
		else if (!strcmp(command[0], "ls"))
		{
			ls();
		}
		else if (!strcmp(command[0], "pinfo"))
		{
			pinfo();
		}
		else if (!strcmp(command[0], "history"))
		{
			if (args > 2)
			{
				printf("Too many arguments\n");
				return;
			}
			history();
		}
		else if (!strcmp(command[0], "repeat"))
		{
			int repeatcount = atoi(command[1]);
			for (int z = 0; z < args-2; z++)
			{
				command[z] = (char *)malloc((strlen(command[z+2])+1)*sizeof(char));
				strcpy(command[z], command[z+2]);
			}
			command[args-2]="";
			command[args-1]="";
			args = args - 2;
			for (int z=0;z<repeatcount;z++)
				execute(args);
		}
		else
		{
			fgbg(bg);
		}
	}
}