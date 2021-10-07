#include "pwd.h"

void pwd()
{
	if (getcwd(curr_dir, sizeof(curr_dir)))
	{
		printf("%s", curr_dir);
	}
	else
	{
		fprintf(stderr,"Error getting current working directory\n");
	}
	printf("\n");
}