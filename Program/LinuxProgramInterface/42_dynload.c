/* ---------------------------- */
/* Using the dlopen API */
/* ---------------------------- */

#include <dlfcn.h>
#include "tlpi_hdr.h"

int main(int argc, char*argv[])
{
    void* libHandler;      /* Handle for shared library */
    void (*funcp)(void);   /* Pointer to function with no argument */
    const char* err;
    Dl_info info;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s lib-path func-name\n", argv[0]);

    /* Load the shared library and get a handler for later use */
    libHandler = dlopen(argv[1], RTLD_LAZY);
    if (libHandler == NULL)
        fatal("dlopen: %s", dlerror());

    /* Search library for symbol named in argv[2] */

    (void)dlerror();       /* Clear dlerror() */
    *(void**)(&funcp) = dlsym(libHandler, argv[2]);
    err = dlerror();
    if (err != NULL)
        fatal("dlsym: %s", err);

    /* If the address returned by dlsym() is non-NULL, try calling it as a*/
    /* function that takes no arguments */
    if (funcp == NULL)
        printf("%s is NULL\n", argv[2]);
    else
        (*funcp)();

    if (dladdr(funcp, &info) != 0)
    {
        printf(info.dli_fname);
        printf(info.dli_sname);
    }


    dlclose(libHandler);   /* Close the library */

    exit(EXIT_SUCCESS);

}
