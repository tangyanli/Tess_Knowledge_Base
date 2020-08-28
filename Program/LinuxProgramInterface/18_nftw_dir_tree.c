/* Author : Tess */
/* Using nftw() to walk a direcotry tree */
/*************************/
#define _XOPEN_SOURCE 600 	/* Get nftw() and S_IFSOCK declarations */
#include <ftw.h>
#include "tlpi_hdr.h"

static void usageError(const char* progName, const char* msg)
{
	if (msg != NULL)
		fprintf(stderr, "%s\n", msg);
	fprintf(stderr, "Usage: %s [-d] [-m] [-p] [directory-path]\n", progName);
	fprintf(stderr, "\t-d Use FTW_DEPTH flag\n");
	fprintf(stderr, "\t-m Use FTW_MOUNT flag\n");
	fprintf(stderr, "\t-p Use FTW_PHYS flag\n");
	exit(EXIT_FAILURE);
}

/* Function called by nftw */
static int dirTree(const char* pathname, const struct stat* sbuf, int type, struct FTW* ftwb)
{
	switch(sbuf->st_mode & S_IFMT)	/* Print file type */
	{
	case S_IFREG:	printf("-"); 	break;
	case S_IFDIR:	printf("d");	break;
	case S_IFCHR:	printf("c");	break;
	case S_IFBLK:	printf("b");	break;
	case S_IFLNK:	printf("l");	break;
	case S_IFIFO:	printf("s");	break;
	default:	printf("?");	break;	/* Should never happen (on Linux) */
	}
	
	if (type != FTW_NS)
		printf("%7ld ", (long)sbuf->st_ino);
	else
		printf("	");
	
	printf(" %s",
		(type == FTW_D) ? "D- Directory" :
		(type == FTW_DNR) ? "DNR - Directory cann't be read" :
		(type == FTW_DP) ? "DP - Postorder traversal" :
		(type == FTW_F) ? "F-Any type other than a directory or symbolic link" :
		(type == FTW_SL) ? "SL - symbolic link" :
		(type == FTW_SLN) ? "SLN - Dangling symbolic link" :
		(type == FTW_NS) ? "NS - Calling stat() on this file failed" : " ");
	
	printf(" %*s", 4*ftwb->level, " "); 	/* Indent suitably*/
	printf("%s\n", &pathname[ftwb->base]);	/* Print basename */
	
	return 0;
}

int main(int argc, char* argv[])
{	
	int flags, opt;
	
	flags = 0;
	while((opt = getopt(argc, argv,"dmp")) != -1)
	{
	   switch(opt) 
	   {
		case 'd': flags |= FTW_DEPTH;	break;
		case 'm': flags |= FTW_MOUNT;	break;
		case 'p': flags |= FTW_PHYS;	break;
		default: usageError(argv[0], NULL);
	   }
	}
	
	if (argc > optind + 1)
		usageError(argv[0], NULL);

	if (nftw((argc > optind) ? argv[optind] : ".", dirTree, 10, flags) == -1)
	{
		perror("nftw");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
