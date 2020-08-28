/* Changing the terminal interrupt character */

#include <termios.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    struct termios tp;
    int intrChar;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [intr-char]\n", argv[0]);

    /* Determine new INTR setting from command line */
    if (argc == 1)     /* Disable */
    {
        intrChar = fpathconf(STDIN_FILENO, _PC_VDISABLE);
        if (intrChar == -1)
            errExit("Couldn't determine VDISABLE ");
    }
    else if (isdigit((unsigned char)argv[1][0]))
    {
        intrChar = strtoul(argv[1], NULL, 0);   /* Allow hex, octal */
    }
    else
    {
        intrChar = argv[1][0];         /* Literal character */
    }

    /*printf("The intrChar is%c.\n", intrChar);
    printf("VDISCARD is %d\n", VDISCARD);
    printf("VEOF is %d\n", VEOF);
    printf("VEOL is %d\n", VEOL);
    printf("VEOL2 is %d\n", VEOL2);
    printf("VERASE is %d\n", VERASE);
    printf("VINTR is %d\n", VINTR);
    printf("VKILL is %d\n", VKILL);
    printf("VLNEXT is %d\n", VLNEXT);
    printf("VQUIT is %d\n", VQUIT);
    printf("VREPRINT is %d\n", VREPRINT);
    printf("VSTART is %d\n", VSTART);
    printf("VSTOP is %d\n", VSTOP);
    printf("VSUSP is %d\n", VSUSP);
    printf("VWERASE is %d\n", VWERASE);*/

    /* Fetch current terminal settings,
       modify INTR character, and
       push changes back to the terminal driver */
    if (tcgetattr(STDIN_FILENO, &tp) == -1)
        errExit("tcgetattr");
    tp.c_cc[VINTR] = intrChar;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
        errExit("tcsetattr");

    exit(EXIT_SUCCESS);
}
