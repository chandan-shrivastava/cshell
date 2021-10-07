#include "sig.h"

void sig()
{
    int job_no, signal;
    job_no = atoi(command[1]);
    signal = atoi(command[2]);
    pid_t pid = findpidbyjobno(head, job_no);
    if (pid)
    {
        if (kill(pid, signal) < 0)
        {
            fprintf(stderr,"Error: Invalid Signal\n");
        }
    }
    else
    {
        fprintf(stderr,"Error: Invalid job number\n");
    }
}