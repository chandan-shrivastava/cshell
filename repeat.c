#include "repeat.h"

void repeat(char cmd[])
{
    int repeatcount = atoi(command[1]);
    for (int z = 0; z < args - 2; z++)
    {
        command[z] = (char *)malloc((strlen(command[z + 2]) + 1) * sizeof(char));
        strcpy(command[z], command[z + 2]);
    }
    command[args - 2] = "";
    command[args - 1] = "";
    args = args - 2;
    for (int z = 0; z < repeatcount; z++)
        execute(cmd);
}