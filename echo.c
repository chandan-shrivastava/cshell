#include "echo.h"

void echo()
{
	for (int i = 1; i < args; i++)
	{
		printf("%s ", command[i]);
	}
	printf("\n");
}
