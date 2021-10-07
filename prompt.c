#include "prompt.h"

void prompt()
{
	gethostname(hostname, 32);
	username = getenv("USER");
	if (getcwd(curr_dir, sizeof(curr_dir)))
	{
		if (strstr(curr_dir, home_dir))
		{
			char *pathfromhome = strstr(curr_dir, home_dir);
			pathfromhome += strlen(home_dir);
			printf(CYAN"<%s@%s:"YELLOW"~%s"RESET">", username, hostname, pathfromhome);
		}
		else
		{
			printf(CYAN"<%s@%s:"YELLOW"%s"RESET">", username, hostname, curr_dir);
		}
	}
	else
	{
		fprintf(stderr,"Error getting current directory\n");
	}
}
