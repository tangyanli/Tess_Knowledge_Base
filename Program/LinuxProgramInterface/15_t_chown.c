/* Author: Tess */
/* Listing 15-2: Changing the owner and group of a file  */
/* ------------------------------------------------ */

#include <pwd.h>
#include <grp.h>
#include "ugid_functions.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
	uid_t uid;
	gid_t gid;
	int j;
	Boolean errFnd;
	
	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s owner group [file...]\n"
			 "	owner or group can be '-',"
			 "meaning leave unchange\n", argv[0]);
	
	if (strcmp(argv[1],"-") == 0)
	{
		uid = -1;	/* Don't change owner */
	}
	else
	{
		uid = userIdFromName(argv[1]);
		if (uid == -1)
			fatal("NO such user (%s)", argv[1]);
	}

	if (strcmp(argv[2],"-") == 0)
	{
		gid = -1;	/* Don't change group */
	}
	else
	{
		gid = groupIdFromName(argv[2]);
		if (gid == -1)
			fatal("NO such group (%s)", argv[2]);
	}

	errFnd = FALSE;
	for (j = 3; j < argc; j++)
	{
		if (chown(argv[j], uid, gid) == -1)
		{
			errMsg("chown: %s", argv[j]);
			errFnd = TRUE;
		}
	}
	

	exit(errFnd ? EXIT_FAILURE: EXIT_SUCCESS);
}





































