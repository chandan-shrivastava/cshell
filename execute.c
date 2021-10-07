#include "execute.h"

void execute(char cmd[])
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
		if (strstr(cmd, "<") || strstr(cmd, ">"))
		{
			redirect(cmd);
			for (int i = 0; i < args; i++)
			{
				if (!strcmp(command[i], ">") || !strcmp(command[i], ">>") || !strcmp(command[i], "<"))
				{
					fprintf(stderr,"Invalid Syntax\n");
					return;
				}
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
		else if (!strcmp(command[0], "replay"))
		{
			replay();
		}
		else if (!strcmp(command[0], "history"))
		{
			if (args > 2)
			{
				fprintf(stderr,"Too many arguments\n");
				return;
			}
			history();
		}
		else if (!strcmp(command[0], "bg"))
		{
			if (args != 2)
			{
				fprintf(stderr, "Incorrect number of arguments");
				return;
			}
			bgfunc();
		}
		else if (!strcmp(command[0], "fg"))
		{
			fg();
		}
		else if (!strcmp(command[0], "jobs"))
		{
			jobs();
		}
		else if (!strcmp(command[0], "sig"))
		{
			if (args != 3)
			{
				fprintf(stderr, "Incorrect number of Arguments\n");
				return;
			}
			sig();
		}
		else if (!strcmp(command[0], "repeat"))
		{
			repeat(cmd);
		}
		else
		{
			fgbg(bg);
		}
	}
}