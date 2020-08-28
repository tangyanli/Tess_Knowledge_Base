/* Header file for id_echo_sv.c and id_echo_cl.c */

#include "59_inet_sockets.h"
#include "tlpi_hdr.h"

#define SERVICE "echo"   /* Name of UPD Service */
#define BUF_SIZE 500     /* Maximum size of datagrams that can be read by client and server */
