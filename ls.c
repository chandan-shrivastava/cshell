#include "ls.h"

int checkmorethan6month(int mon1, int day1, int year1, int mon2, int day2, int year2)
{
	int day_diff, mon_diff, year_diff;
	if (day2 < day1)
	{
		if (mon2 == 3)
		{
			if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
			{
				day2 += 29;
			}
			else
			{
				day2 += 28;
			}
		}
		else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
		{
			day2 += 30;
		}
		else
		{
			day2 += 31;
		}
		mon2 = mon2 - 1;
	}
	if (mon2 < mon1)
	{
		mon2 += 12;
		year2 -= 1;
	}
	day_diff = day2 - day1;
	mon_diff = mon2 - mon1;
	year_diff = year2 - year1;
	if (year_diff >= 1 || mon_diff >= 6)
	{
		return 1;
	}
	else
		return 0;
}

void lsfull(char filepath[], char *file)
{
	struct stat f = {0};
	if (stat(filepath, &f) == 0)
	{
		if (S_ISLNK(f.st_mode))
			permissions[0] = 'l';
		else if (S_ISREG(f.st_mode))
			permissions[0] = '-';
		else if (S_ISDIR(f.st_mode))
			permissions[0] = 'd';
		else if (S_ISCHR(f.st_mode))
			permissions[0] = 'c';
		else if (S_ISBLK(f.st_mode))
			permissions[0] = 'b';
		else if (S_ISFIFO(f.st_mode))
			permissions[0] = 'p';
		else if (S_ISSOCK(f.st_mode))
			permissions[0] = 's';
		else
			permissions[0] = 's';
		permissions[1] = ((f.st_mode & S_IRUSR) ? 'r' : '-');
		permissions[2] = ((f.st_mode & S_IWUSR) ? 'w' : '-');
		permissions[3] = ((f.st_mode & S_IXUSR) ? 'x' : '-');
		permissions[4] = ((f.st_mode & S_IRGRP) ? 'r' : '-');
		permissions[5] = ((f.st_mode & S_IWGRP) ? 'w' : '-');
		permissions[6] = ((f.st_mode & S_IXGRP) ? 'x' : '-');
		permissions[7] = ((f.st_mode & S_IROTH) ? 'r' : '-');
		permissions[8] = ((f.st_mode & S_IWOTH) ? 'w' : '-');
		permissions[9] = ((f.st_mode & S_IXOTH) ? 'x' : '-');
		permissions[10] = '\0';
		char mtime[80];
		char mtime1[80];
		char year[80];
		char month[80];
		char date[80];
		time_t t = f.st_mtime;
		struct tm lt;
		localtime_r(&t, &lt);
		time_t t1 = time(NULL);
		struct tm tm = *localtime(&t1);
		int curr_year = tm.tm_year + 1900;
		int curr_month = tm.tm_mon + 1;
		int curr_day = tm.tm_mday;
		strftime(year, sizeof mtime, "%Y", &lt);
		strftime(month, sizeof mtime, "%m", &lt);
		strftime(date, sizeof mtime, "%d", &lt);
		strftime(mtime, sizeof mtime, "%b %d %H:%M", &lt);
		strftime(mtime1, sizeof mtime1, "%b %d %Y", &lt);
		struct passwd *pw = getpwuid(f.st_uid);
		struct group *gr = getgrgid(f.st_gid);
		int returnfunc = checkmorethan6month(atoi(month), atoi(date), atoi(year), curr_month, curr_day, curr_year);
		if (returnfunc == 1)
		{
			printf("%s  %ld\t%s\t%s\t%ld\t%s  %s\n", permissions, f.st_nlink, pw->pw_name, gr->gr_name, f.st_size, mtime1, file);
		}
		else
		{
			printf("%s  %ld\t%s\t%s\t%ld\t%s  %s\n", permissions, f.st_nlink, pw->pw_name, gr->gr_name, f.st_size, mtime, file);
		}
	}
	else
	{
		fprintf(stderr,"Error reading file permission!\n");
	}
}

void lspath(char path[], int lsl, int lsa)
{
	struct stat path_stat;
	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		char *filename;
		filename = basename(path);
		if (lsl)
		{
			lsfull(path, filename);
		}
		else
		{
			printf("%s\n", filename);
		}
		return;
	}
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d)
	{
		printf("%s:\n", path);
		if (lsl)
		{
			long long total = 0;
			while ((dir = readdir(d)) != NULL)
			{
				char filepath[2048];
				strcpy(filepath, path);
				strcat(filepath, "/");
				strcat(filepath, dir->d_name);

				struct stat direc = {0};
				if (stat(filepath, &direc) == 0)
					total += direc.st_blocks;
			}
			printf("total %lld\n", total / 2);
			rewinddir(d);
		}
		while ((dir = readdir(d)) != NULL)
		{
			char filepath[2048];
			strcpy(filepath, path);
			strcat(filepath, "/");
			strcat(filepath, dir->d_name);

			if (lsl && lsa)
			{
				lsfull(filepath, dir->d_name);
			}
			else if (lsl && !lsa)
			{
				if (dir->d_name[0] != '.')
				{
					lsfull(filepath, dir->d_name);
				}
			}
			else if (!lsl && lsa)
			{
				printf("%s\n", dir->d_name);
			}
			else if (!lsl && !lsa)
			{
				if (dir->d_name[0] != '.')
				{
					printf("%s\n", dir->d_name);
				}
			}
		}
	}
	else
	{
		struct stat f = {0};
		if (stat(path, &f) == 0)
		{
			if (lsl)
			{
				lsfull(path, path);
			}
			else
			{
				printf("%s\n", path);
			}
			printf("\n");
		}
		else
		{
			fprintf(stderr,"Error opening directory or file!\n");
		}
	}
}

void ls()
{
	int lsl = 0, lsa = 0, dir_present = 0;
	for (int i = 1; i < args; i++)
	{
		if (!strcmp(command[i], "-l"))
			lsl = 1;
		else if (!strcmp(command[i], "-a"))
			lsa = 1;
		else if (!strcmp(command[i], "-al") || !strcmp(command[i], "-la"))
		{
			lsl = 1;
			lsa = 1;
		}
		else if (strcmp(command[i], ""))
		{
			dir_present = 1;
		}
	}
	if (!dir_present)
	{
		char path[] = ".";
		lspath(path, lsl, lsa);
	}
	else
	{
		for (int i = 1; i < args; i++)
		{
			if (!strcmp(command[i], "-l") || !strcmp(command[i], "-a") || !strcmp(command[i], "-al") || !strcmp(command[i], "-la"))
				continue;
			else
			{
				char path[1024];
				if (strstr(command[i], "~"))
				{
					char *name = command[i];
					name++;
					strcpy(path, home_dir);
					strcat(path, name);
				}
				else
				{
					strcpy(path, command[i]);
				}
				lspath(path, lsl, lsa);
			}
		}
	}
}