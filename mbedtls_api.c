
#include <stdio.h>
#include <string.h>
#include "mbedtls_api.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/certs.h"
#include "mbedtls/debug.h"

const char * root_certificate =
		#if 0
		"-----BEGIN CERTIFICATE-----\n"
		"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\n"
		"A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n"
		"b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\n"
		"MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n"
		"YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\n"
		"aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\n"
		"jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\n"
		"xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n"
		"1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\n"
		"snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\n"
		"U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n"
		"9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\n"
		"BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\n"
		"AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\n"
		"yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n"
		"38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\n"
		"AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\n"
		"DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\n"
		"HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
		"-----END CERTIFICATE-----\n";
#endif
#if 0
"-----BEGIN CERTIFICATE-----\n"
"MIIDfDCCAmSgAwIBAgIQGKy1av1pthU6Y2yv2vrEoTANBgkqhkiG9w0BAQUFADBY\n"
"MQswCQYDVQQGEwJVUzEWMBQGA1UEChMNR2VvVHJ1c3QgSW5jLjExMC8GA1UEAxMo\n"
"R2VvVHJ1c3QgUHJpbWFyeSBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTAeFw0wNjEx\n"
"MjcwMDAwMDBaFw0zNjA3MTYyMzU5NTlaMFgxCzAJBgNVBAYTAlVTMRYwFAYDVQQK\n"
"Ew1HZW9UcnVzdCBJbmMuMTEwLwYDVQQDEyhHZW9UcnVzdCBQcmltYXJ5IENlcnRp\n"
"ZmljYXRpb24gQXV0aG9yaXR5MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n"
"AQEAvrgVe//UfH1nrYNke8hCUy3f9oQIIGHWAVlqnEQRr+92/ZV+zmEwu3qDXwK9\n"
"AWbK7hWNb6EwnL2hhZ6UOvNWiAAxz9juapYC2e0DjPt1befquFUWBRaa9OBesYjA\n"
"ZIVcFU2Ix7e64HXprQU9nceJSOC7KMgD4TCTZF5SwFlwIjVXiIrxlQqD17wxcwE0\n"
"7e9GceBrAqg1cmuXm2bgyxx5X9gaBGgeRwLmnWDiNpcB3841kt++Z8dtd1k7j53W\n"
"kBWUvEI0EME5+bEnPn7WinXFsq+W06Lem+SYvn3h6YGttm/81w7a4DSwDRp35+MI\n"
"mO9Y+pyEtzavwt+s0vQQBnBxNQIDAQABo0IwQDAPBgNVHRMBAf8EBTADAQH/MA4G\n"
"A1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQULNVQQZcVi/CPNmFbSvtr2ZnJM5IwDQYJ\n"
"KoZIhvcNAQEFBQADggEBAFpwfyzdtzRP9YZRqSa+S7iq8XEN3GHHoOo0Hnp3DwQ1\n"
"6CePbJC/kRYkRj5KTs4rFtULUh38H2eiAkUxT87z+gOneZ1TatnaYzr4gNfTmeGl\n"
"4b7UVXGYNTq+k+qurUKykG/g/CFNNWMziUnWm07Kx+dOCQD32sfvmWKZd7aVIl6K\n"
"oKv0uHiYyjgZmclynnjNS6yvGaBzEi38wkG6gZHaFloxt/m0cYASSJlyc1pZU8Fj\n"
"UjPtp8nSOQJw+uCxQmYpqptR7TBUIhRf2asdweSU8Pj1K/fqynhG1riR/aYNKxoU\n"
"AT6A8EKglQdebc3MS6RFjasS6LPeWuWgfOgPIh1a6Vk=\n"
"-----END CERTIFICATE-----\n";
#endif
#if 1
"-----BEGIN CERTIFICATE-----\n"
"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\n"
"A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n"
"b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\n"
"MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n"
"YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\n"
"aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\n"
"jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\n"
"xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n"
"1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\n"
"snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\n"
"U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n"
"9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\n"
"BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\n"
"AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\n"
"yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n"
"38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\n"
"AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\n"
"DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\n"
"HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
"-----END CERTIFICATE-----\n";
#endif

typedef struct {
	mbedtls_net_context server_fd;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_ssl_context ssl;
	mbedtls_ssl_config conf;
	mbedtls_x509_crt cacert;
} mbedtls_socket_context_t;

static void my_debug( void *ctx, int level,
							 const char *file, int line,
							 const char *str )
{
	((void) level);

#if defined __link
	fprintf( (FILE *) ctx, "%s:%04d: %s", file, line, str );
	fflush(  (FILE *) ctx  );
#else
	mcu_debug_printf("mbedtls:%s:%04d: %s", file, line, str);
#endif
}

int sslVerify(void * ctx,
				  mbedtls_x509_crt *crt,
				  int depth,
				  uint32_t *flags){
	int ret = 0;

	/*
	  * If MBEDTLS_HAVE_TIME_DATE is defined, then the certificate date and time
	  * validity checks will probably fail because this application does not set
	  * up the clock correctly. We filter out date and time related failures
	  * instead
	  */
	*flags &= ~MBEDTLS_X509_BADCERT_FUTURE & ~MBEDTLS_X509_BADCERT_EXPIRED;


	return ret;
}

//initialize
int tls_initialize(void * context){
	return 0;
}

//create
int tls_socket(void ** context, int domain, int type, int protocol){
	int result;
	const char *pers = "Mbed TLS helloword client";
	mbedtls_socket_context_t * mbedtls_context = malloc(sizeof(mbedtls_socket_context_t));
	if( mbedtls_context == 0 ){
		return -1;
	}

	mbedtls_entropy_init( &mbedtls_context->entropy );
	mbedtls_ctr_drbg_init( &mbedtls_context->ctr_drbg );
	mbedtls_x509_crt_init( &mbedtls_context->cacert );
	mbedtls_net_init( &mbedtls_context->server_fd );
	mbedtls_ssl_init( &mbedtls_context->ssl );
	mbedtls_ssl_config_init( &mbedtls_context->conf );

	mbedtls_ctr_drbg_seed( &mbedtls_context->ctr_drbg,
								  mbedtls_entropy_func,
								  &mbedtls_context->entropy,
								  (const unsigned char *) pers,
								  strlen( pers ) );

	if( (result = mbedtls_x509_crt_parse( &mbedtls_context->cacert,
													  (const u8 *)root_certificate,
													  strlen(root_certificate) + 1 )) < 0 ){
		mcu_debug_printf("failed to crt parse %X\n", -1*result);
		return -1;
	}


	//call socket directly
	mbedtls_context->server_fd.fd = socket(domain, type, protocol);
	if( mbedtls_context->server_fd.fd < 0 ){
		free(mbedtls_context);
		return -1;
	}

	*context = mbedtls_context;
	mcu_debug_printf("tls socket is returning 0\n");
	return 0;
}

//connect
int tls_connect(void * context, const struct sockaddr *address, socklen_t address_len, const char * server_name){
	int ret;
	int flags;

	mbedtls_socket_context_t * mbedtls_context = context;

	//net_connect calls socket and connect and getaddrinfo -- just call connect directly
	//mbedtls_net_connect( &mbedtls_context->server_fd, "SERVER_NAME", 8080, MBEDTLS_NET_PROTO_TCP );

	if( connect(mbedtls_context->server_fd.fd, address, address_len) < 0 ){
		mcu_debug_printf("Failed to connect at socket level %d (0x%X) to %s\n", mbedtls_context->server_fd.fd, mbedtls_context->server_fd.fd);
		return -1;
	}

	if( ( ret = mbedtls_ssl_config_defaults( &mbedtls_context->conf,
														  MBEDTLS_SSL_IS_CLIENT,
														  MBEDTLS_SSL_TRANSPORT_STREAM,
														  MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
	{
		mcu_debug_printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\n\n", ret );
		return -1;
	}

	mbedtls_ssl_conf_authmode( &mbedtls_context->conf, MBEDTLS_SSL_VERIFY_OPTIONAL );
	mbedtls_ssl_conf_ca_chain( &mbedtls_context->conf, &mbedtls_context->cacert, NULL );
	mbedtls_ssl_conf_rng( &mbedtls_context->conf, mbedtls_ctr_drbg_random, &mbedtls_context->ctr_drbg );
#if defined __link
	mbedtls_ssl_conf_dbg( &mbedtls_context->conf, my_debug, stdout );
#else
	mbedtls_ssl_conf_dbg( &mbedtls_context->conf, my_debug, 0 );
#endif
	mbedtls_debug_set_threshold(0);

	if( ( ret = mbedtls_ssl_setup( &mbedtls_context->ssl, &mbedtls_context->conf ) ) != 0 ){
		mcu_debug_printf("Failed to ssl setup\n");
		return -1;
	}

	mbedtls_ssl_conf_verify(&mbedtls_context->conf, sslVerify, 0);


	if( ( ret = mbedtls_ssl_set_hostname( &mbedtls_context->ssl, server_name) ) != 0 ){
		mcu_debug_printf("Failed to set host name\n");
		return -1;
	}

	mbedtls_ssl_set_bio( &mbedtls_context->ssl,
								&mbedtls_context->server_fd,
								mbedtls_net_send,
								mbedtls_net_recv,
								NULL);


	while( ( ret = mbedtls_ssl_handshake( &mbedtls_context->ssl ) ) != 0 ){
		if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
		{
			mcu_debug_printf("handshake failed (%X)\n", ret*-1);
			return -1;
		}
	}


	/* In real life, we probably want to bail out when ret != 0 */
	if( ( flags = mbedtls_ssl_get_verify_result( &mbedtls_context->ssl ) ) != 0 ){
		char vrfy_buf[512];
		mbedtls_x509_crt_verify_info( vrfy_buf, sizeof( vrfy_buf ), "  ! ", flags );
	}

	return 0;
}

//read
int tls_read(void * context, void * buf, int nbyte){
	mbedtls_socket_context_t * mbedtls_context = context;
	return mbedtls_ssl_read( &mbedtls_context->ssl, buf, nbyte );
}

//write
int tls_write(void * context, const void * buf, int nbyte){
	mbedtls_socket_context_t * mbedtls_context = context;
	return mbedtls_ssl_write( &mbedtls_context->ssl, buf, nbyte );
}

//close
int tls_close(void ** context){
	mbedtls_socket_context_t * mbedtls_context = *context;
	*context = 0;
	mbedtls_ssl_close_notify( &mbedtls_context->ssl );
	mbedtls_net_free( &mbedtls_context->server_fd );
	mbedtls_x509_crt_free( &mbedtls_context->cacert );
	mbedtls_ssl_free( &mbedtls_context->ssl );
	mbedtls_ssl_config_free( &mbedtls_context->conf );
	mbedtls_ctr_drbg_free( &mbedtls_context->ctr_drbg );
	mbedtls_entropy_free( &mbedtls_context->entropy );
	return 0;
}

const mbedtls_api_t mbedtls_api = {
	.socket = tls_socket,
	.close = tls_close,
	.read = tls_read,
	.write = tls_write,
	.connect = tls_connect
};

#if !defined __link

unsigned long mbedtls_timing_hardclock( void ){
	 struct timespec now;
	 clock_gettime(CLOCK_REALTIME, &now);
	 return now.tv_sec * 1000000 + now.tv_nsec / 1000UL;
}


#endif


//for server implementation
//bind_and_listen
//int tls_bind_and_listen();
//accept
