#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <termios.h>

#include "cd.h"
#include "echo.h"
#include "execute.h"
#include "fgbg.h"
#include "history.h"
#include "ls.h"
#include "main.h"
#include "pinfo.h"
#include "prompt.h"
#include "pwd.h"
#include "bg.h"
#include "fg.h"
#include "jobs.h"
#include "linked.h"
#include "sig.h"
#include "pipes.h"
#include "redirect.h"
#include "signal.h"
#include "replay.h"
#include "repeat.h"

#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

char *inputs[1000];
char temp_inputs[1000];
char temp_pipe[1000];
char curr_fg_name[1000];
int curr_fg_pid;
char *command[1000];
char *temporary[1000];
char home_dir[1000];
char curr_dir[1000];
char hostname[1000];
char *username;
char prev_dir[1000];
int args;
char his[100][1000];
char permissions[11];
int h;
int jobno;
pid_t shellpid;
char line[1000];
struct Node
{
    pid_t pid;
    char name[1024];
    int job;
    struct Node *next;
};
struct Node *head;
int shellin, shellout;

#endif