#include <sys/stat.h>
#include <stdio.h>
#include "file_perms.h"

#define STR_SIZE sizeof("rwxrwxrwx")

/* Return ls -l stryle string for file permission mask*/
char* filePermStr(mode_t perm, int flags)
{
	static char str[STR_SIZE];
	
	snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
		(perm & S_IRUSR) ? 'R' : '-',
		(perm & S_IWUSR) ? 'W' : '-',
     		(perm & S_IXUSR) ? 'x' : '-',
		(perm & S_IRGRP) ? 'R' : '-',
		(perm & S_IWGRP) ? 'W' : '-',
     		(perm & S_IXGRP) ? 'x' : '-',
		(perm & S_IROTH) ? 'R' : '-',
		(perm & S_IWOTH) ? 'W' : '-',
     		(perm & S_IXOTH) ? 'x' : '-');
	
	return str;
}


























































































