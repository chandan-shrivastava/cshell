#include "main.h"

void clearScreen()
{
	printf("\033[H\033[J");
}

int removewhitespaces(char str[])
{
	int i = 0;
	char *token = strtok(str, " \t\n");
	if (token != NULL)
	{
		command[i++] = token;
	}
	while (token != NULL)
	{
		token = strtok(NULL, " \t\n");
		if (token != NULL)
		{
			command[i++] = token;
		}
	}
	return i;
}

void signal_handler(int signal)
{
	int status;
	char *name;
	pid_t pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0)
	{
		if (!status)
			fprintf(stderr, "\n%s with pid %d exited normally\n", pid1[pid], pid);
		else
			fprintf(stderr, "\n%s with pid %d exited abnormally\n", pid1[pid], pid);
		prompt();
		fflush(stdout);
	}
}

int main()
{
	int ch;
	clearScreen();
	getcwd(curr_dir, sizeof(curr_dir));
	strcpy(prev_dir, "");
	strcpy(home_dir, curr_dir);
	h = prevhistory();
	signal(SIGCHLD, signal_handler);
	shellpid = getpid();
	int xyz = 0;
	FILE *fp;
	fp = fopen("history.txt", "w");
	fclose(fp);
	while (1)
	{
		prompt();
		size_t bufSize = 0;
		int readlines;
		char *scan = 0;
		xyz += 1;
		readlines = getline(&scan, &bufSize, stdin);
		if (readlines < 0)
		{
			printf("\n");
			exit(0);
		}
		if (scan[0] == '\0')
			continue;
		int i = 0;
		char *token = strtok(scan, ";");
		if (token != NULL)
		{
			inputs[i++] = token;
		}
		while (token != NULL)
		{
			token = strtok(NULL, ";");
			if (token != NULL)
			{
				inputs[i++] = token;
			}
		}
		for (int j = 0; j < i; j++)
		{
			if (inputs[j] != NULL)
			{
				char *lastline = getlastline();
				strcat(lastline, "\n");
				if (xyz == 1 || strcmp(lastline, inputs[j]) != 0)
				{
					strcpy(his[h++ % 20], inputs[j]);
					writehistorytofile(inputs[j]);
				}
				args = removewhitespaces(inputs[j]);
				execute();
			}
		}
	}
	free(inputs);
	return 0;
}