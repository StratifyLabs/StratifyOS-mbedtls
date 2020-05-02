
include(sources.cmake)

set(SOS_SOURCELIST
	${TLS_SOURCES}
	${X509_SOURCES}
	${SOURCES}
	${HEADERS}
	${SOURCES_PREFIX}/net_sockets.c
	config/mbedtls/config.h
	mbedtls_link_config.h
	link_config.c
	timing_alt.h
	mbedtls_api.h
	mbedtls_api.c
	mbedtls_crypt_api.c
	threading.c)

set(SOS_OPTION "")
set(SOS_CONFIG release)
set(SOS_ARCH link)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib.cmake)
