#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "ugid_functions.h"

/* Return name corresponding to uid, or NULL on error */
char* userNameFromId(uid_t uid)
{
	struct passwd* pwd;
	
	pwd = getpwuid(uid);
	return (pwd == NULL) ? NULL : pwd->pw_name;
}

/* Return UID corresponding to name or -1 on error*/
uid_t userIdFromName(const char* name)
{
	struct passwd* pwd;
	uid_t u;
	char* endptr;
	
	if ((name == NULL)||(*name == '\0'))
		return -1;
	
	u = strtol(name, &endptr, 10);	/* As a convenience to caller */
	if (*endptr == '\0')
		return u;
	
	pwd = getpwnam(name);
	if (pwd == NULL)
		return -1;
	
	return pwd->pw_uid;
}

/* Return name corresponding to 'gid', or NULL on error */
char* groupNameFromId(gid_t gid)
{
	struct group* grp;
	
	grp = getgrgid(gid);
	return (grp == NULL) ? NULL : grp->gr_name;
}

/* Return GID corresponding to 'name', or -1 on error */
gid_t groupIdFromName(const char* name)
{
	struct group* grp;
	gid_t g;
	char* endptr;
	
	if (name == NULL || *name == '\0')
		return -1;

	g = strtol(name, &endptr, 10);	/* As a convenience to caller */
	if (*endptr == '\0')
		return g;
	
	grp = getgrnam(name);
	if (grp == NULL)
		return -1;
	
	return grp->gr_gid;
}






































