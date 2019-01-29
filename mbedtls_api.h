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

#define MBEDTLS_API_T 1 //increment when adding functions

typedef struct {

	//enough for a client
	int (*socket)(void ** context, int domain, int type, int protocol);
	int (*connect)(void * context, const struct sockaddr *address, socklen_t address_len, const char * server_name);
	int (*close)(void ** context);
	int (*write)(void * context, const void * buf, int nbyte);
	int (*read)(void * context, void * buf, int nbyte);
	int (*fileno)(void * context);
	int (*write_ticket)(void * context, void * buf, int nbyte, u32 lifetime);
	int (*parse_ticket)(void * context, void * buf, int nbyte);

	//server
	//bind_and_listen()
	//accept()

} mbedtls_api_t;

extern const mbedtls_api_t mbedtls_api;

#if defined __link
#define MBEDTLS_API_REQUEST &mbedtls_api
#else
#define MBEDTLS_API_REQUEST MCU_API_REQUEST_CODE('m','t','l','s')
#endif


#endif /* MBEDTLS_API_H */
