
include(sources.cmake)

set(SOS_LIB_SOURCELIST
	${TLS_SOURCES}
	${X509_SOURCES}
	${SOURCES}
	${HEADERS}
	${SOURCES_PREFIX}/net_sockets.c
	link_config.h
	link_config.c
	timing_alt.h
	mbedtls_api.h
	mbedtls_api.c
	threading.c)

set(SOS_LIB_OPTION "")
set(SOS_LIB_TYPE release)
set(SOS_LIB_DEFINITIONS -DMBEDTLS_CONFIG_FILE="link_config.h")
set(SOS_LIB_ARCH link)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib.cmake)
