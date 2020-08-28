/* Implementation of readn() and writen() */

#include <unistd.h>
#include <errno.h>
#include "rdwrn.h"

ssize_t readn(int fd, void *buffer, size_t n)
{
    ssize_t numRead;
    size_t totRead;
    char *buf;

    buf = buffer;
    for (totRead = 0; totRead < n; )
    {
        numRead = read(fd, buf, n-totRead);

        if (numRead == 0)      /* EOF */
            return totRead;    /* May be 0 if this is first read() */
        if (numRead == -1)
        {
            if (errno == EINTR)
                continue;          /* Interrupted --> restart read() */
            else
                return -1;
        }

        totRead += numRead;
        buf += numRead;
    }

    return totRead;            /* Must be 'n' bytes if we get here */
}

ssize_t writen(int fd, const void *buffer, size_t n)
{
    ssize_t numWritten;
    size_t totWritten;
    const char *buf;

    buf = buffer;
    for (totWritten = 0; totWritten < n; )
    {
        numWritten = write(fd, buf, n-totWritten);

        if (numWritten <= 0)
        {
            if (numWritten == -1 && errno == EINTR)
                continue;              /* Interrupted --> restart write() */
            else
                return -1;             /* Some other error */
        }

        totWritten += numWritten;
        buf += numWritten;
    }

    return totWritten;       /* Must be 'n' bytes if we get here */
}
