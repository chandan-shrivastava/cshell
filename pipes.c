#include "pipes.h"
#include "execute.h"

int separate(char str[], char *pipeCommands[32])
{
    int i = 0;
    char *token = strtok(str, "|");
    if (token != NULL)
        pipeCommands[i++] = token;
    while (token != NULL)
    {
        token = strtok(NULL, "|");
        if (token != NULL)
            pipeCommands[i++] = token;
    }
    return i;
}

void execpipe(char cmd[])
{
    strcpy(his[h++ % 20], cmd);
    int numpipes = 0;
    for (int i = 0; i < strlen(cmd); i++)
    {
        if (cmd[i] == '|')
            numpipes++;
    }
    char *pipeCommands[32];
    int pipe_commands = separate(cmd, pipeCommands);
    if (pipe_commands != numpipes + 1)
    {
        fprintf(stderr, "Invalid Syntax\n");
        return;
    }
    int fds[pipe_commands - 1][2];
    for (int i = 0; i < pipe_commands - 1; i++)
    {
        if (pipe(fds[i]) < 0)
        {
            fprintf(stderr,"Error in piping command\n");
        }
        if (!i)
        {
            int out = dup(STDOUT_FILENO);
            dup2(fds[i][1], STDOUT_FILENO);
            close(fds[i][1]);
            strcpy(temp_pipe,pipeCommands[i]);
            args = removewhitespaces(pipeCommands[i]);
            execute(temp_pipe);
            dup2(out, STDOUT_FILENO);
            close(out);
        }
        else
        {
            int in = dup(STDIN_FILENO);
            int out = dup(STDOUT_FILENO);
            dup2(fds[i][1], STDOUT_FILENO);
            dup2(fds[i - 1][0], STDIN_FILENO);
            close(fds[i][1]);
            close(fds[i - 1][0]);
            strcpy(temp_pipe,pipeCommands[i]);
            args = removewhitespaces(pipeCommands[i]);
            execute(temp_pipe);
            dup2(in, STDIN_FILENO);
            dup2(out, STDOUT_FILENO);
            close(in);
            close(out);
        }
    }
    int in = dup(STDIN_FILENO);
    dup2(fds[pipe_commands - 2][0], STDIN_FILENO);
    close(fds[pipe_commands - 2][0]);
    strcpy(temp_pipe,pipeCommands[pipe_commands - 1]);
    args = removewhitespaces(pipeCommands[pipe_commands - 1]);
    execute(temp_pipe);
    dup2(in, STDIN_FILENO);
    close(in);
}
