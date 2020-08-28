#include "become_daemon.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    becomeDaemon(BD_NO_CHDIR);

    exit(EXIT_SUCCESS);
}
