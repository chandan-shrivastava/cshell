# C-Shell

To compile the shell, run:
```bash
make
```
After compilation, to start the shell run:
```bash
./c-shell
```

## [main.c](main.c)

This is the main file for the shell's execution. On execution the shell clears the terminal for smooth execution. It sets up the Home Directory. The history is loaded at this point, and the main while loop is activated, waiting for human interaction. It is also responsible to handle white spaces sepearated commands. If there are several instructions on a single line, the **;** is used to separate them and call execution for each of them. It also handles the execution of background process when it exits.

## [headers.h](headers.h)

This file contains all the libraries needed for the execution of the shell. It also contains all the global variables used throughout the running of the shell.

## [execute.c](execute.c)

This file handles the excution of all the commands. The commands are checked with the arguments and executed as per the need.

## [cd.c](cd.c)

This file contains the implementation of the **cd** command used to change directories. Usage:
```bash
cd ../
cd -
cd *dirname*
```

## [echo.c](echo.c)

This file contains the implementation of the **echo** command used to print text on the shell. Usage:
```bash
echo *text*
```

## [pwd.c](pwd.c)

This file contains the implementation of the **pwd** command used to get the current working directory. Usage:
```bash
pwd
```

## [ls.c](ls.c)

This file contains the implementation of the **ls** command used to get the contents of a directory. It handles two types of flags: _-a_ and _-l_ have also been implemented. The falgs can be in any order. It can also show the contents of various directories given as its arguments. If the file is more than 6 months old then **ls -l** changes the modified time to year. Usage:
```bash
ls
ls *flags*
ls *flags* *dir*
```


## [pinfo.c](pinfo.c)

This file contains the implementation of the user defined **pinfo** command which can be used to get the process information of the current process by default or a process specified by its pid which is given as argument. This command shows the pid specified, Process status whether it is running, sleeping, zombine or stopped. The status has a **+** if the process is running in foreground. It also shows the Virtual memory and the executable path of the process. Usgae:
```bash
pinfo
pinfo *pid*
```

## [fgbg.c](fgbg.c)

This file contains the implementation for the execution of foreground and background processes. Background processes can be run by placing an **&** at the end of the command. The variable **_back_** is set to 1 if the process is a background process or 0 if it is a foreground process. Usage:  
```bash
gedit &
firefox &
vim &
```

## [prompt.c](prompt.c)

This file contains the implementation of the **prompt** which is to be printed before any command the user enters. It showcases the username, hostname, and the current working directory.

## [history.c](history.c)

This file contains the implementation of the **history** command used to display the users most recent commands. It shows the 10 most recent commands by default but the number of commands to be shown can be given as an argument. The previous session history is loaded again on start of the shell. While running the commands are stored in an array to reduce overhead of reading and writing from a file. If the last command is same as of the command entered then it is not added to the file. We do not store more than previous 90 commands. It keeps deleting oldest 10 command once excedding 90 commands.
```bash
history
history *num*
```

## [bg.c](bg.c)

This file conatains the command **bg** command which is used to change status of a background process from running to stopped. Usage:
```bash
bg *job_no*
```

## [fg.c](fg.c)

This file conatains the command **fg** command which is used to bring a background process into the foreground and it change its status from stopped to running if required. Usage:
```bash
fg *job_no*
```

## [jobs.c](jobs.c)

This file conatains the command **jobs** command which displays all the current background processes with their pid and job number in increasing alphabetical order. Implemented 2 flags -r and -s respectively to show running and stopped processes respectively.Usgae:
```bash
jobs
jobs -r
jobs -s
```

## [sig.c](sig.c)

This file conatains the command **sig** command which can be used to send a signal to a background process by its job number. Usage:
```bash
sig *job_no* *signal_no*
```

## [pipes.c](pipes.c)

This file is used to implement the pipe functionality in the commands. Usage:
```bash
cat sig.c | wc -l > lines.txt
```

## [redirect.c](redirect.c)

This file is used to implement the redirect of input/output functionality in the commands. Usage:
```bash
cat < sig.c >> sig1.c
```

## [signal.c](signal.c)

This file contains the implementation of the signal handler to receive the SIGCHILD signal from the child background processes. After receiving the signal it determines whether the child process terminated normally and prints it to stderr along with its name, pid and status. It also includes the signal handlers for dealing with SIGINT and SIGTSTP signal related to <kbd>Ctrl</kbd> <kbd>C</kbd> and <kbd>Ctrl</kbd> <kbd>Z</kbd>.

## [linked.c](linked.c)

This file contains the implementation of a linked list to store the background processes and sorting function to sort the linked list for jobs command. 

## [replay.c](replay.c)

This file contains the implementation of **replay** command which executes a particular command in fixed time interval for a certain period. YOu cannot execute another command while it is running. Usage: 
```bash
replay -command *command* -interval *interval* -period *period*
```

## [repeat.c](repeat.c)
This file contains the implementation of **repeat** command which executes a particular command multiple times at once. Usage:
```bash
repeat *no_of_times* *command* 
```
