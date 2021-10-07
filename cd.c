#include "cd.h"

void cd()
{
	getcwd(curr_dir, sizeof(curr_dir));
	if (args == 1 || !strcmp(command[1], "~"))
	{
		if (chdir(home_dir) < 0)
		{
			fprintf(stderr,"Error changing directory\n");
		}
		else
		{
			strcpy(prev_dir, curr_dir);
		}
	}
	else if (strstr(command[1], "~"))
	{
		char *name = command[1];
		name++;
		strcpy(curr_dir, home_dir);
		strcat(curr_dir, name);
		if (chdir(curr_dir) < 0)
		{
			fprintf(stderr,"Error changing directory\n");
		}
		else
		{
			strcpy(prev_dir, curr_dir);
		}
	}
	else if (!strcmp(command[1], "-"))
	{
		if (strcmp(prev_dir, ""))
		{
			printf("%s\n", prev_dir);
			if (chdir(prev_dir) < 0)
			{
				fprintf(stderr,"Error changing directory\n");
			}
			else
			{
				strcpy(prev_dir, curr_dir);
			}
		}
		else
		{
			fprintf(stderr,"OLDPWD not set\n");
		}
	}
	else
	{
		if (chdir(command[1]) < 0)
		{
			fprintf(stderr,"Error changing directory\n");
		}
		else
		{
			strcpy(prev_dir, curr_dir);
		}
	}
}