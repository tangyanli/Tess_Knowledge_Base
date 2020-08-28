/* Author: Tess						 	    */
/* Listing 23-8: Using the timerfd API				    */
/*------------------------------------------------------------------*/

#include <sys/timerfd.h>
#include <time.h>
#include <stdint.h>
#include "itimerspec_from_str.h"
#include "tlpi_hdr.h"			/* Declars itimerspecFromStr() */

int main(int argc, char* argv[])
{
	struct itimerspec ts;
	struct timespec start, now;
	int maxExp, fd, secs, nanosecs;
	uint64_t numExp, totalExp;
	ssize_t s;
	
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s secs[/nsecs][:int-secs[/int-nsecs]] [max-exp]\n", argv[0]);
	
	itimerspecFromStr(argv[1], &ts);
	maxExp = (argc > 2) ? getInt(argv[2], GN_GT_0, "max-exp") : 1;
	
	/* Create and start a fd-timer */	
	fd = timerfd_create(CLOCK_REALTIME, 0);
	if (fd == -1)
		errExit("timerfd_create");
	
	if (timerfd_settime(fd, 0, &ts, NULL) == -1)
		errExit("timerfd_settime");
			
	if (clock_gettime(CLOCK_MONOTONIC,&start) == -1)
		errExit("clock_gettime");
	
	for (totalExp = 0; totalExp < maxExp;)
	{
		/* Read number of expirations on the timer, and then display
		   time elapsed since timer was started, followed by number 
		   of expirations read and total expirations so far */
		
		s = read(fd, &numExp, sizeof(uint64_t));
		if (s != sizeof(uint64_t))
			errExit("read");
		
		totalExp += numExp;
	
		if (clock_gettime(CLOCK_MONOTONIC, &now) == -1)
			errExit("clock_gettime");
		
		secs = now.tv_sec - start.tv_sec;
		nanosecs = now.tv_nsec - start.tv_nsec;
		if (nanosecs < 0)
		{
			secs--;
			nanosecs += 1000000000;
		}
		
		printf("%d.%03d: expirations read: %llu; total=%llu\n",
			secs, (nanosecs + 500000) / 1000000,
			(unsigned long long) numExp,
			(unsigned long long) totalExp);

	}

	exit(EXIT_SUCCESS);

}
