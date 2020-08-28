#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	int fd, j, numBlocks;
	char shellCmd[CMD_SIZE];		/* Command to be passed to system() */
	char buf[BUF_SIZE];			/* Random bytes to write to file */
	
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s temp-file [num-1kb-blocks]\n", argv[0]);
	
	numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kb-blocks") : 100000;
	
	fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd == -1)
		errExit("open");
	
	if (unlink(argv[1]) == -1)			/* Remove filename */
		errExit("unlink");
	
	for (j = 0; j < numBlocks; j++)
		if (write(fd, buf, BUF_SIZE) != BUF_SIZE)	/* write lots of junk to file*/
			fatal("partial/failed write");

	snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
	system(shellCmd);		/* View space used in file system */
	
	if (close(fd) == -1)		/* File is now destroyed */
		errExit("close");
	printf("********** closed file descriptor\n");
	
	system(shellCmd);		/* Review spece used in file system*/
	exit(EXIT_SUCCESS);
		
	
}
