#ifndef TTY_FUNCTION_H
#define TTY_FUNCTION_H

#include <termios.h>
#include <unistd.h>

int ttySetCbreak(int fd, struct termios *prevTermios);
int ttySetRaw(int fd, struct termios *prevTermios);

#endif
