/* Author: Tess*/
/* Listing 22-5: Using sigsuspend()*/
/*----------------------*/

#define _GNU_SOURCE	/* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <signal.h>
#include <time.h>
#include "signal_functions.h"	/* Declarations of printSigMask() and printPendingSigs */
#include "tlpi_hdr.h"

static volatile sig_atomic_t gotSigquit = 0;

static void handler(int sig)
{
	printf("Caught signal %d (%s)\n", sig, strsignal(sig));		/* UNSAFE (see section 21.2.2) */
	
	if (sig == SIGQUIT)
		gotSigquit = 1;
}


int main(int argc, char* argv[])
{
	int loopNum;
	time_t startTime;
	sigset_t origMask, blockMask;
	struct sigaction sa;
	
	/* Step1 */
	printSigMask(stdout, "Initial signal mask is:\n"); 
	
	sigemptyset(&blockMask);
	sigaddset(&blockMask, SIGINT);
	sigaddset(&blockMask, SIGQUIT);
	
	/* Step2 */	
	if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
		errExit("sigprocmask - SIG_BLOCK");
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	
	/* Step3 */
	if (sigaction(SIGINT, &sa, NULL) == -1)
		errExit("sigaction");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		errExit("sigaction");
	
	/* Step4 */
	for (loopNum = 1; !gotSigquit; loopNum++)
	{
		printf("=== LOOP %d\n", loopNum);
		
		/* Simulate a critical section by delaying a few seconds */
		printSigMask(stdout, "Starting critical section, signal mask is:\n");
		
		for (startTime = time(NULL); time(NULL) < startTime + 4;)
			continue;		/* Run for a few seconds elapsed time */
	
		printPendingSigs(stdout, "Before sigsuspend() -pending signals:\n");
		
		if (sigsuspend(&origMask) == -1 && errno != EINTR)
			errExit("sigsuspend");
	}

	/* Step5 */	
	if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
		errExit("sigprocmask - SIG_SETMASK");
	
	/* Step6 */
	printSigMask(stdout, "=== Exited loop\nRestored signal mask to:\n");
	
	exit(EXIT_SUCCESS);
}
