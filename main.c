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

int main()
{
	int ch;
	// clearScreen();
	jobno = 0;
	getcwd(curr_dir, sizeof(curr_dir));
	strcpy(prev_dir, "");
	strcpy(home_dir, curr_dir);
	h = prevhistory();
	signal(SIGCHLD, signal_handler);
	signal(SIGINT, signal_control_c);
	signal(SIGTSTP, signal_control_z);
	shellpid = getpid();
	int xyz = 0;
	FILE *fp;
	fp = fopen("history.txt", "w");
	fclose(fp);
	curr_fg_pid = 0;
	shellin = dup(STDIN_FILENO);
	shellout = dup(STDOUT_FILENO);
	while (1)
	{
		prompt();
		size_t bufSize = 0;
		curr_fg_pid = 0;
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
		{
			continue;
		}
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
		if (!strcmp(inputs[0], "\n"))
		{
			continue;
		}
		for (int j = 0; j < i; j++)
		{
			if (inputs[j] != NULL)
			{
				curr_fg_pid = 0;

				char *lastline = getlastline();
				strcat(lastline, "\n");
				if (xyz == 1 || strcmp(lastline, inputs[j]) != 0)
				{
					strcpy(his[h++ % 20], inputs[j]);
					writehistorytofile(inputs[j]);
				}
				strcpy(temp_inputs, inputs[j]);
				args = removewhitespaces(inputs[j]);
				if (strstr(temp_inputs, "|"))
				{
					int len = strlen(temp_inputs);
					if (temp_inputs[len - 1] == '\n')
						temp_inputs[len - 1] = 0;
					execpipe(temp_inputs);
				}
				else
				{
					execute(temp_inputs);
				}
				dup2(shellin, STDIN_FILENO);
				dup2(shellout, STDOUT_FILENO);
			}
		}
	}
	free(inputs);
	return 0;
}