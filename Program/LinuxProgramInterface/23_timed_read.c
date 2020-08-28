/* Author: Tess*/
/* Listing 23-2: Performing a read() with timeout */
/*----------------------*/

#include <signal.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 200

static void handler(int sig)
{
	printf("Caught signal\n");		/* UNSAFE (see section 21.1.2)*/
}


int main(int argc, char* argv[])
{
	struct sigaction sa;
	char buf[BUF_SIZE];
	ssize_t numRead;
	int savedErrno;
	
	if (argc > 1 && strcmp(argv[1], "--help") == 0)
		usageErr("%s [num-secs [Restart-flag]]\n, argv[0]");
	
	/* Set up handler for SIGALRM. */
	/* Allow system calls to be interrrupted, unless second command-line argument was supplied. */
	sa.sa_flags = (argc > 2) ? SA_RESTART : 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	if (sigaction(SIGALRM, &sa, NULL) == -1)
		errExit("sigaction");

	alarm((argc > 1) ? getInt(argv[1], GN_NONNEG, "num-secs") : 10);
	numRead = read(STDIN_FILENO, buf, BUF_SIZE -1);
	
	savedErrno = errno;	/* In case alarm() changes it */
	alarm(0);		/* Ensure timer is truned off */
	errno = savedErrno;
	
	/* Determine result of read */
	if (numRead == -1)
	{
		if (errno == EINTR)	/* EINTR: Interrupted function */
			printf("Read timed out\n");
		else
			errMsg("Read");
	}
	else
	{
		printf("Successful read (%ld bytes): %.*s", (long)numRead, (int)numRead, buf);
	}
	
	exit(EXIT_SUCCESS);
}
