/* An implementation of strerror() that is not thread-safe */
/* --------------------------------------------------------*/
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "tlpi_hdr.h"

#define MAX_ERROR_LEN 256
static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t strerrorKey;

/* Free thread-specific data buffer */
static void destructor(void *buf)
{
    printf("Free block stoage (%p)\n", buf);
    free(buf);
}

/* One-time key creation function */
static void createKey(void)
{
    int s;

    printf("Create Key\n");

    /* Allocate a unique thread-specific data key and save the address
     of the destructor for thread-specific data buffers */
    s = pthread_key_create(&strerrorKey, destructor);
    if (s != 0)
        errExitEN(s, "pthread_key_create");
}

char* strerror(int err)
{
    int s;
    char *buf;

    /* Make first caller allocate key for thread-specific data */
    s = pthread_once(&once, createKey);
    if (s != 0)
        errExitEN(s, "pthread_once");

    buf = pthread_getspecific(strerrorKey);
    if (buf == NULL)
    {
        buf = malloc(MAX_ERROR_LEN);
        if (buf == NULL)
            errExit("malloc");

        s = pthread_setspecific(strerrorKey, buf);
        if (s != 0)
            errExitEN(s, "pthread_setspecific");

        printf("Malloc memory (%p)\n", buf);
    }

    if (err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL)
    {
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
    }
    else
    {
        strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
        buf[MAX_ERROR_LEN - 1] = '\0';    /* Ensure null termination */
    }

    return buf;
}

static void* threadFunc(void *arg)
{
    char *str;
    int errors[3] = {EPERM, EINVAL, ESRCH};

    printf("Other thread about to call strerror()\n");
    for (int index = 0; index < 3; index++)
    {
        str = strerror(errors[index]);
        printf("Other thread: str (%p) = %s\n", str, str);
    }

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
