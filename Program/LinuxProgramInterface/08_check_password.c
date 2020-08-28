#define _BSD_SOURCE	/* Get getpass() declaration from <unistd.h> */
#define _XOPEN_SOURCE	/* Get crypt() declaration from <unistd.h> */

#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "tlpi_hdr.h"

int main(int argc, char*argv[])
{
	char *username, *password, *encrypted, *p;
	struct paswd *pwd;
	struct spwd *spwd;
	Boolean authOk;
	size_t len;
	long lnmax;
	
	lnmax = sysconf(_SC_LOGIN_NAME_MAX);
	if (lnmax == -1)		/* If limit is indeterminate */
		lnmax = 256;		/* make a guess */
	
	username = malloc(lnmax);
	if (username == NULL)
		errExit("malloc");
	
	printf("Username:	");
	fflush(stdout);
	if (fgets(username, lnmax, stdin) == NULL)
		exit(EXIT_FAILURE);	
	
	len = strlen(username);
	if (username[len -1] == '\n')
		username[len-1] = '\0';
	
	pwd = getpwnam(username);
	if (pwd == NULL)
		fatal("couldn't get password record");
	
	spwd = getspnam(username);
	if (spwd == NULL && errno == EACCES)
		fatal("no permission to read shadow password file");
	
	if (spwd != NULL)
		pwd->pw_passwd = spwd->sp_pwdp;		/* use the shadow password */
	
	password = getpass("Password: ");
	
	/* Encrypt password and erase clearext version immediately */
	encrypted = crypt(password, pwd->pw_passwd);
	for (p = password; *p != '\0'; )
		*p++ = '\0';
	
	if (encrypted == NULL)
		errExit("crypt");
	
	authOk = strcmp(encrypted, pwd->pw_passwd) == 0;
	if (!authOk)
	{
		printf("Incorrect password\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);
	
	exit(EXIT_SUCCESS);
}































































