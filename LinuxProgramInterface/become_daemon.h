/* ------------------------------  */
/* Header file for become_daemon.c */
/* --------------------------------*/
#ifndef  BECOME_DAEMON_H
#define BECOME_DAEMON_H

/* Bit-mask values for 'flags' argument of becomeDaemon() */
#define BD_NO_CHDIR                 0x1   /* Don't chdir("/") */
#define BD_NO_CLOSE_FILES           0x2   /* Don't close all open files */
#define BD_NO_REOPEN_STD_FDS        0x4   /* Don't reopen stdin, stdout, and stderr to /dev/null */
#define BD_NO_UMASKo                0x10  /* Don't do a unmask (o) */
#define BD_MAX_CLOSE                8192 /* Maximum file descriptors to close if sysconf (_SC_OPEN_MAX) is indeterminate*/

int becomeDaemon(int flags);

#endif
