#include "pinfo.h"

void processstatus(int pid)
{
	char path2[1024], path[1024];
	sprintf(path2, "/proc/%d/stat", pid);
	sprintf(path, "/proc/%d/status", pid);
	FILE *fp = fopen(path, "r");
	FILE *fp1 = fopen(path2, "r");
	char *line1 = NULL;
	char *line = NULL;
	size_t len = 0, read;
	int flag = 0;
	if (fp1 == NULL)
	{
		fprintf(stderr,"Error opening %s file\n", path2);
	}
	else
	{
		long long pgrp, tpgid;
		char str[1024];
		int i = 1;
		while (fscanf(fp1, "%s", str) == 1)
		{
			if (i == 5)
				pgrp = atoi(str);
			if (i == 8)
			{
				tpgid = atoi(str);
				break;
			}
			i++;
		}
		if (pgrp == tpgid)
			flag = 1;
		fclose(fp1);
	}
	if (fp == NULL)
	{
		fprintf(stderr,"Error opening %s file\n", path);
	}
	else
	{
		int line_no = 0;
		while ((read = getline(&line, &len, fp)) != -1)
		{
			line_no++;
			if (line_no == 3)
			{
				char *token = strtok(line, " \t");
				token = strtok(NULL, " \t");
				printf("Process Status -- {%s", token);
				if (flag == 1)
					printf("+");
				printf("}\n");
				break;
			}
		}
		fclose(fp);
	}
}

void memory(int pid)
{
	char path[1024];
	sprintf(path, "/proc/%d/status", pid);
	FILE *fp = fopen(path, "r");
	char *line = NULL;
	size_t len = 0, read;
	int flag = 0;
	if (fp == NULL)
	{
		fprintf(stderr,"Error opening %s file\n", path);
	}
	else
	{
		int line_no = 0;
		while ((read = getline(&line, &len, fp)) != -1)
		{
			line_no++;
			if (line_no == 18)
			{
				char *token = strtok(line, " \t");
				token = strtok(NULL, " \t");
				printf("memory -- %s {​Virtual Memory​}\n", token);
				break;
			}
		}
		fclose(fp);
	}
}

void executable(int pid)
{
	char path1[1024], buf[1024];
	sprintf(path1, "/proc/%d/exe", pid);
	FILE *fp3 = fopen(path1, "r");
	size_t ret = readlink(path1, buf, 1024);
	if (fp3 == NULL)
	{
		fprintf(stderr,"Error opening %s file\n", path1);
	}
	else if (ret > 0)
	{
		buf[ret] = 0;
		if (strstr(buf, home_dir))
		{
			char *short_path = strstr(buf, home_dir);
			short_path += strlen(home_dir);
			printf("Executable Path -- ~%s\n", short_path);
		}
		else
		{
			printf("Executable Path -- %s\n", buf);
		}
	}
	else
	{
		fprintf(stderr,"Error opening %s file\n", path1);
	}
}

void pinfo()
{
	pid_t pid;
	if (args > 1)
	{
		pid = atoi(command[1]);
	}
	else
	{
		pid = shellpid;
	}
	printf("pid -- %d\n", pid);
	processstatus(pid);
	memory(pid);
	executable(pid);
}