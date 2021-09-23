# C-Shell

To compile the shell, run:
```bash
make
```
After compilation, to start the shell run:
```bash
./cshell
```

## main.c

This is the main file for the shell's execution. On execution the shell clears the terminal for smooth execution. It sets up the Home Directory. The history is loaded at this point, and the main while loop is activated, waiting for human interaction. It is also responsible to handle white spaces sepearated commands. If there are several instructions on a single line, the **;** is used to separate them and call execution for each of them. It also handles the execution of background process when it exits.

```c
int main();
void signal_handler(int signal);
void signal_control(int signal);
int removewhitespaces(char str[]);
char *getlastline();
void clearScreen();
```

## headers.h

This file contains all the libraries needed for the execution of the shell. It also contains all the global variables used throughout the running of the shell.

## execute.c

This file handles the excution of all the commands. The commands are checked with the arguments and executed as per the need.

```c
void execute();
```

## cd.c

This file contains the implementation of the **cd** command used to change directories.

```c
void cd();
```

## echo.c

This file contains the implementation of the **echo** command used to print text on the shell.

```c
void echo();
```

## pwd.c

This file contains the implementation of the **pwd** command used to get the current working directory.

```c
void pwd()
```

## ls.c

This file contains the implementation of the **ls** command used to get the contents of a directory. It handles two types of flags: _-a_ and _-l_ have also been implemented. The falgs can be in any order. It can also show the contents of various directories given as its arguments. If the file is more than 6 months old then **ls -l** changes the modified time to year.

```c
void ls();
void lsfull(char filepath[], char *file);
void lspath(char path[], int full, int hide);
int checkmorethan6month(int mon1, int day1, int year1, int mon2, int day2, int year2);
```

## pinfo.c

This file contains the implementation of the user defined **pinfo** command which can be used to get the process information of the current process by default or a process specified by its pid which is given as argument. This command shows the pid specified, Process status whether it is running, sleeping, zombine or stopped. The status has a **+** if the process is running in foreground. It also shows the Virtual memory and the executable path of the process.

```c
void pinfo();
void processstatus(int pid);
void memory(int pid);
void executable(int pid);
```

## fgbg.c

This file contains the implementation for the execution of foreground and background processes. Background processes can be run by placing an **&** at the end of the command.

```c
void fgbg(int bgorfg);
```

The variable **_back_** is set to 1 if the process is a background process or 0 if it is a foreground process.

## prompt.c

This file contains the implementation of the **prompt** which is to be printed before any command the user enters. It showcases the username, hostname, and the current working directory.

```c
void prompt();
```

## history.c

This file contains the implementation of the **history** command used to display the users most recent commands. It shows the 10 most recent commands by default but the number of commands to be shown can be given as an argument. The previous session history is loaded again on start of the shell. While running the commands are stored in an array to reduce overhead of reading and writing from a file. If the last command is same as of the command entered then it is not added to the file. We do not store more than previous 90 commands. It keeps deleting oldest 10 command once excedding 90 commands.

```c
int prevhistory();
void writehistorytofile(char cmd[]);
void history();
int text_delete();
char *getlastline();
```


