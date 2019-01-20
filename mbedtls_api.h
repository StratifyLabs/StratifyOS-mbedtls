#ifndef MBEDTLS_API_H
#define MBEDTLS_API_H

#include <mcu/types.h>

#if defined __win32
#define _BSD_SOURCE
#include <winsock2.h>
#include <ws2tcpip.h>
typedef u32 in_addr_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#endif

//what is the top level API
#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"

extern const mbedtls_api_t mbedtls_api;


#endif /* MBEDTLS_API_H */
