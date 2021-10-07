#include "bg.h"

void bgfunc()
{
    int jnum = atoi(command[1]);
    pid_t pid = findpidbyjobno(head, jnum);
    if (pid <= 0)
    {
        fprintf(stderr, "Invalid job number\n");
        return;
    }
    if (kill(pid, SIGCONT) < 0)
    {
        fprintf(stderr,"Error in continuing process\n");
    }
}