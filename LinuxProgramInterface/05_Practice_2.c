#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
	int fd;	
	
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file\n", argv[0]);

	fd = open(argv[1], O_RDWR | O_APPEND);
	if (fd == -1)
		errExit("open");
	
	lseek(fd, 0, SEEK_CUR);
	write(fd, "Practice_2", 10);
	
	close(fd);	
	exit(EXIT_SUCCESS);	
}
