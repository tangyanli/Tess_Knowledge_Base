#include "tlpi_hdr.h"

/* Print 'msg' plus value of fpathconf(fd, name) */
static void fpathconfPrint(const char*msg, int fd, int name)
{
	long lim;
	
	errno = 0;
	lim = fpathconf(fd, name);
	if (lim != -1)	/* call succeeded, limit determinate */
	{
		printf("%s %ld\n", msg, lim);
	}
	else
	{
		if (errno == 0)
			printf("%s (indeterminate)\n", msg);	/* call successed, limit indeterminate */
		else
			errExit("fpathconf %s", msg);	/* call failed */
	}	
}

int main(int argc, char* argv[])
{
	fpathconfPrint("_PC_NAME_MAX:	",  STDIN_FILENO,	_PC_NAME_MAX);
	fpathconfPrint("_PC_PATH_MAX:	",  STDIN_FILENO,	_PC_PATH_MAX);
	fpathconfPrint("_PC_PIPE_BUF:	",  STDIN_FILENO,	_PC_PIPE_BUF);
		
	exit(EXIT_SUCCESS);
}





































