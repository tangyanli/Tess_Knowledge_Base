/*---------------------------------------------------- */
/* Using select() to monitor multiple file descriptors */
/* ----------------------------------------------------*/

#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <termios.h>
#include <sys/select.h>
#include "pty_fork.h"
#include "tty_functions.h"
#include "tlpi_hdr.h"

#define BUF_SIZE 256
#define MAX_SNAME 10000

struct termios ttyOrig;

static void ttyRest(void)
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, &ttyOrig) == -1)
        errExit("tcsetattr");
}

int main(int argc, char* argv[])
{
    char slaveName[MAX_SNAME];
    char *shell;
    int masterFd, scriptFd;
    struct winsize ws;
    fd_set inFds;
    char buf[BUF_SIZE];
    ssize_t numRead;
    pid_t childPid;

    /* 1. Retrieve the attributes and window size of the terminal under which
     the program is run*/
    if (tcgetattr(STDIN_FILENO, &ttyOrig) == -1)
        errExit("tcgetattr");
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0)
        errExit("ioctl-TIOCGWINSZ");

    /* 2. Call ptyFork() function to create a child process that is connected to
     the parent via a pseudoterminal pair */
    childPid = ptyFork(&masterFd, slaveName, MAX_SNAME, &ttyOrig, &ws);
    if (childPid == -1)
        errExit("ptyFOrk");

    /* Child Process */
    if (childPid == 0)    /* Child: execute a shell on pty slave */
    {
        shell = getenv("SHELL");
        if (shell == NULL || *shell == '\0')
            shell = "/bin/sh";

        /* Change working fold */
        chdir("~/Linux_c");

        /* 3.4. After the ptyFork() call, the child execs a shell.
         The choice of shell is determined by the setting of the
        SHELL environment variable.
        If the SHELL variable is not set or its value is an empyt string,
        then the child execs /bin/sh */
        execlp(shell, shell, (char*)NULL);
        errExit("execlp");   /* If we get here, something went wrong */

        //write(STDOUT_FILENO, "Slave write Hello\n", 18);
    }
    else
    {

    /* Parent: Relay data between terminal and pty master */
    /* 5. Open the output script file.
       If a command-line argument is supplied,this is used as the name of the script file.
       If no command-line argument is supplied, the default name typescript is usend. */
    scriptFd = open((argc > 1) ? argv[1] : "typescript",
                    O_WRONLY | O_CREAT | O_TRUNC,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (scriptFd == -1)
        errExit("open typescript");

    /*6. Place the terminal in raw mode, so that all input characters are passed directly
     to the script program without being modified by the terminal driver.
    characters output by the script program are likewise not modified by the terminal driver.*/
    ttySetRaw(STDIN_FILENO, &ttyOrig);

    /*7. Call atexit() to install an exit handler that resets the terminal
      to its original mode when the program terminates. */
    if (atexit(ttyRest) != 0)
        errExit("atexit");

    for(;;)
    {
        FD_ZERO(&inFds);
        FD_SET(STDIN_FILENO, &inFds);
        FD_SET(masterFd, &inFds);

        /* 9. In each loop iteration, the program first use select() to
         monitor both the terminal and the pseudoterminal master for input. */
        if (select(masterFd+1, &inFds, NULL, NULL, NULL) == -1)
            errExit("select");

        /*10. If the terminal has input available, then the program reads some
         of that input and writes it to the pseudoterminal master.*/
        if (FD_ISSET(STDIN_FILENO, &inFds))
        {
            numRead = read(STDIN_FILENO, buf, BUF_SIZE);
            if (numRead <= 0)
                exit(EXIT_SUCCESS);

            if (write(masterFd, buf, numRead) != numRead)
                fatal("partial/failed write (masterFd)");
        }

        /*11. If the pseudoterminal master has input available, the program reads some
         of that input and writes it to the terminal and to the script file.*/
        if (FD_ISSET(masterFd, &inFds))
        {
            numRead = read(masterFd, buf, BUF_SIZE);
            if (numRead < 0)
                exit(EXIT_SUCCESS);

            //printf("Read data from masterFd: %s\n", buf);
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                fatal("partial/failed write (STDOUT_FILENO)");
            if (write(scriptFd, buf, numRead) != numRead)
                fatal("partial/failed write (scriptFd)");
            //write(masterFd, buf, numRead);
        }
    }
    }
}
