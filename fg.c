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
    strcpy(name, findnamebypid(head, pid));
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(0, getpgid(pid));
    if (kill(pid, SIGCONT) < 0)
    {
        fprintf(stderr,"Error while running command\n");
    }
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpgid(shellpid));
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    head = deletejob(head, pid);
}