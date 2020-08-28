/* An implementation of strerror() that is not thread-safe */
/* --------------------------------------------------------*/
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "tlpi_hdr.h"

#define MAX_ERROR_LEN 256
static char buf[MAX_ERROR_LEN];

char* strerror(int err)
{
    if (err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL)
    {
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
    }
    else
    {
        strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN-1);
        buf[MAX_ERROR_LEN - 1] = '\0';   /* Ensure null termination */
    }

    return buf;
}

static void* threadFunc(void *arg)
{
    char *str;

    printf("Other thread about to call strerror()\n");
    str = strerror(EPERM);
    printf("Other thread: str (%p) = %s\n", str, str);

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t t;
    int s;
    char* str;

    str = strerror(EINVAL);
    printf("Main thread has called strerror()\n");

    s = pthread_create(&t, NULL, threadFunc, NULL);
    if (s!=0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("Main Thread: str (%p) = %s\n", str, str);

    exit(EXIT_SUCCESS);

}
