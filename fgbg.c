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
	strcpy(curr_fg_name, command[0]);
	for (int i = 1; i < j; i++)
	{
		strcat(curr_fg_name, " ");
		strcat(curr_fg_name, command[i]);
	}
	if (!bgorfg)
	{
		curr_fg_pid = fgbgpid;
	}
	else
	{
		curr_fg_pid=0;
	}
	// printf("%d",fgbgpid);
	if (fgbgpid < 0)
	{
		printf("Failed forking\n");
	}
	else if (!fgbgpid)
	{
		setpgid(0, 0);
		if (execvp(command[0], command) < 0)
		{
			fprintf(stderr,"Error executing %s command\n", command[0]);
			exit(1);
		}
	}
	dup2(shellout, STDOUT_FILENO);
	dup2(shellin, STDIN_FILENO);
	if (bgorfg)
	{
		char name[1024];
		strcpy(name, command[0]);
		for (int i = 1; i < j; i++)
		{
			strcat(name, " ");
			strcat(name, command[i]);
		}
		struct Node *temp = head;
		int jnum = 1;
		while (temp != NULL)
		{
			jnum = temp->job + 1;
			temp = temp->next;
		}
		head = newjob(head, fgbgpid, name, jnum);
		printf("%d\n", fgbgpid);
	}
	else
	{
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		tcsetpgrp(0, fgbgpid);
		waitpid(fgbgpid, &pidstatus, WUNTRACED);
		tcsetpgrp(0, shellpid);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		if (WIFSTOPPED(pidstatus))
            {
                char name[1024];
                strcpy(name, command[0]);
                for (int i = 1; i < j; i++)
                {
                    strcat(name, " ");
                    strcat(name, command[i]);
                }

                struct Node *temp = head;
                int jnum = 1;
                while (temp != NULL)
                {
                    jnum = temp->job + 1;
                    temp = temp->next;
                }
                head = newjob(head, fgbgpid, name, jnum);
                printf("\n%s with PID %d suspended\n", name, fgbgpid);
            }
	}
}
