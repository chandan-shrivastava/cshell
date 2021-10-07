#include "redirect.h"

void redirect(char *new_cmd)
{
    if (strstr(new_cmd, "<"))
    {
        int in;
        for (int i = 0; i < args - 1; i++)
        {
            if (!strcmp(command[i], "<"))
            {
                in = open(command[i + 1], O_RDONLY);

                if (in < 0)
                {
                    fprintf(stderr,"Error opening input file\n");
                    return;
                }
                else
                {
                    dup2(in, STDIN_FILENO);
                    close(in);
                }
                command[i] = "";
                command[i + 1] = "";
                break;
            }
        }
    }
    if (strstr(new_cmd, ">"))
    {
        int out;
        for (int i = 0; i < args - 1; i++)
        {
            if (!strcmp(command[i], ">") || !strcmp(command[i], ">>"))
            {
                if (!strcmp(command[i], ">>"))
                {
                    out = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    out = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }

                if (out < 0)
                {
                    fprintf(stderr,"Error opening output file\n");
                }
                else
                {
                    dup2(out, STDOUT_FILENO);
                    close(out);
                }
                command[i] = "";
                command[i + 1] = "";
                break;
            }
        }
    }
}