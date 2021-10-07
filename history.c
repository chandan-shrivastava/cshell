#include "history.h"

char *getlastline()
{
	FILE *fd;
	char filename[] = "history.txt";
	if ((fd = fopen(filename, "r")) != NULL)
	{
		fseek(fd, 0, SEEK_SET);
		while (!feof(fd))
		{
			fscanf(fd, "%[^\n]\n", line);
		}
	}
	return line;
}

int text_delete()
{
	int N=10;
	FILE *f;
	FILE *ftmp;
	int c;
	char file_name[1024];
	strcpy(file_name, home_dir);
	strcat(file_name, "/");
	strcat(file_name, "history.txt");
	f = fopen(file_name, "rt");
	char tmpfile_name[1024];
	strcpy(tmpfile_name, home_dir);
	strcat(tmpfile_name, "/");
	strcat(tmpfile_name, "temp.txt");
	ftmp = fopen(tmpfile_name, "wt");
	if ((f == NULL) || (ftmp == NULL))
	{
		return -1;
	}
	while ((c = fgetc(f)) != EOF)
	{
		if ((char)c == '\n')
		{
			if (--N == 0)
				break;
		}
	}
	while ((c = fgetc(f)) != EOF)
	{
		fputc(c, ftmp);
	}
	fclose(f);
	fclose(ftmp);
	if (remove(file_name) < 0)
		return -1;
	if (rename(tmpfile_name, file_name) < 0)
		return -1;
	return 0;
}

int prevhistory()
{
	char file_name[1024];
	strcpy(file_name, home_dir);
	strcat(file_name, "/");
	strcat(file_name, "history.txt");
	FILE *file;
	file = fopen(file_name, "r");
	char *line = NULL;
	size_t len = 0, readfile;

	h = 0;
	if (file)
	{
		while ((readfile = getline(&line, &len, file)) != -1)
		{
			line[readfile - 1] = '\0';
			strcpy(his[h++], line);
		}
		fclose(file);
	}
	return h;
}

void writehistorytofile(char cmd[])
{
	char file_name[1024];
	strcpy(file_name, home_dir);
	strcat(file_name, "/");
	strcat(file_name, "history.txt");
	FILE *file;
	file = fopen(file_name, "r");
	char chr = getc(file);
	int count_lines = 0;
	if (file == NULL)
	{
		fprintf(stderr,"Unable to write history to file %s\n", file_name);
		return;
	}
	while (chr != EOF)
	{
		if (chr == '\n')
		{
			count_lines = count_lines + 1;
		}
		chr = getc(file);
	}
	fclose(file);
	file = fopen(file_name, "a");
	if(count_lines>90)
	{
		text_delete();
	}
	fprintf(file, "%s", cmd);
	fclose(file);
}

void history()
{
	int inp, num;
	if (args == 2)
	{
		inp = atoi(command[1]);
		if (inp > h)
		{
			if (h > 20)
			{
				inp = 20;
			}
			else
			{
				inp = h;
			}
		}
		if (inp > 20)
		{
			inp = 20;
		}
	}
	else
	{
		inp = h > 10 ? 10 : h;
	}
	num = inp;
	for (int j = (20 + h % 20 - inp) % 20; num > 0; num--, j = (j + 1) % 20)
	{
		printf("%s\n", his[j]);
	}
}