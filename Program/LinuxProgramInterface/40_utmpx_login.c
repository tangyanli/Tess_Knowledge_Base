/* ----------------- */
/* Updating the utmp and wtmp files */
/* ----------------- */

#define _GNU_SOURCE
#include <time.h>
#include <utmpx.h>
#include <lastlog.h>
#include <paths.h>
#include <fcntl.h>
#include "ugid_functions.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    struct utmpx ut;
    struct lastlog llog;
    char* devname;
    int fd;
    uid_t uid;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s username [sleep-time]\n", argv[0]);

    /* Initialize login record for utmp and wtmp files */
    memset(&ut, 0, sizeof(struct utmpx));
    ut.ut_type = USER_PROCESS;   /* This is a user login */
    strncpy(ut.ut_user, argv[1], sizeof(ut.ut_user));

    if (time((time_t*)&ut.ut_tv.tv_sec) == -1)
        errExit("time");  /* Stamp with current time */

    ut.ut_pid = getpid();

    devname = ttyname(STDIN_FILENO);
    if (devname == NULL)
        errExit("ttyname");
    if (strlen(devname) <=8)
        fatal("Terminal name is too short: %s", devname);

    strncpy(ut.ut_line, devname+5, sizeof(ut.ut_line));
    strncpy(ut.ut_id, devname+8, sizeof(ut.ut_id));

    printf("Creating login entries in utmp and wtmp\n");
    printf("    using pid %ld, line %.*s, id %.*s\n",
           (long)ut.ut_pid,
           (int)sizeof(ut.ut_line),
           ut.ut_line,
           (int)sizeof(ut.ut_id),
           ut.ut_id);

    setutxent();  /* Rewind to start of utmp file */
    if (pututxline(&ut) == NULL)  /* Write login record to utmp */
        errExit("pututxline");
    updwtmpx(_PATH_WTMP, &ut);   /* Append login record to wtmp */

    /*Sleep a while, so we can examine utmp and wtmp files*/
    sleep((argc > 2) ? getInt(argv[2], GN_NONNEG, "sleep-time"):15);

    /* Now do a "logout"; use value from previously initialized 'ut', except for changes below */
    ut.ut_type = DEAD_PROCESS;
    time((time_t *)&ut.ut_tv.tv_sec);
    memset(&ut.ut_user, 0, sizeof(ut.ut_user));
    printf("creating logout entries in utmp and wtmp\n");
    setutxent();
    if (pututxline(&ut) == NULL)
        errExit("pututxline");
    updwtmpx(_PATH_WTMP, &ut);   /* Append logout record to wtmp*/

    endutxent();

    /* Practice: 40-2, modify the lastlog file.*/
    fd = open(_PATH_LASTLOG, O_RDWR);
    if (fd != -1)
    {
        uid = userIdFromName(argv[1]);
        if (uid != -1)
        {
            if (lseek(fd, uid*sizeof(struct lastlog), SEEK_SET) != -1)
            {
                llog.ll_time = time(NULL);
                strncpy(llog.ll_line, "pts/20", UT_NAMESIZE);
                strncpy(llog.ll_host, "tess_host", UT_HOSTSIZE);
                write(fd, &llog, sizeof(struct lastlog));

                printf("Write to lastlog file successfully\n");
            }
        }

        close(fd);
        }

    exit(EXIT_SUCCESS);
}
