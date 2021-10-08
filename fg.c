#include "headers.h"

void fg()
{
    char name[1024];
    int job = atoi(command[1]);
    int status;
    pid_t pid = findpidbyjobno(head, job);
    if (pid <= 0)
    {
        fprintf(stderr, "Invalid job number\n");
        return;
    }
    int j=0;
    for (int i = 0; i < args; i++)
	{
		if (strcmp(command[i], ""))
		{
			command[j++] = command[i];
		}
	}
    strcpy(name, findnamebypid(head, pid));
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(0, getpgid(pid));
    if (kill(pid, SIGCONT) < 0)
    {
        fprintf(stderr, "Error while running command\n");
    }
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpgid(shellpid));
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    if (WIFSTOPPED(status))
    {
        struct Node *temp = head;
        int jnum = 1;
        while (temp != NULL)
        {
            jnum = temp->job + 1;
            temp = temp->next;
        }
        printf("\n%s with PID %d suspended\n", name, pid);
        return;
    }
    head = deletejob(head, pid);
}