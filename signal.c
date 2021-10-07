#include "signal.h"

void signal_handler(int signal)
{
	int status;
	char *name;
	pid_t pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0)
	{
		name = findnamebypid(head, pid);
		if (!status)
			fprintf(stderr, "\n%s with pid %d exited normally\n", name, pid);
		else
			fprintf(stderr, "\n%s with pid %d exited abnormally\n", name, pid);
		head = deletejob(head, pid);
		prompt();
		fflush(stdout);
	}
}

void signal_control_c(int signal)
{
	printf("\n");
	prompt();
	fflush(stdout);
}

void signal_control_z(int signal)
{
	printf("\n");
	prompt();
	fflush(stdout);
}