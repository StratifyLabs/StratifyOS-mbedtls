
include(${CMAKE_SOURCE_DIR}/sources.cmake)

set(FORMAT_SOURCELIST
	mbedtls_api.h
	mbedtls_api.c
	mbedtls_crypt_api.c
	)

set(PRIVATE_SOURCELIST
	${TLS_SOURCES}
	${X509_SOURCES}
	${SOURCES}
	${HEADERS}
	${FORMAT_SOURCELIST}
	config/mbedtls/config.h
	mbedtls_sos_config.h
	net_sockets.c
	timing_alt.h
	threading.c)

set(SOS_OPTION kernel)
set(SOS_DEFINITIONS ${SOS_DEFINITIONS} -DHAVE_LWIP_SOCKETS_H)

sos_sdk_library_target(RELEASE mbedtls kernel release v7m)

add_library(${RELEASE_TARGET} STATIC)

target_sources(${RELEASE_TARGET}
	PUBLIC
	${PUBLIC_SOURCES}
	PRIVATE
	${PRIVATE_SOURCELIST}
	)

target_compile_definitions(${RELEASE_TARGET}
	PUBLIC
	${SOS_DEFINITIONS}
	PRIVATE
	IS_LOCAL_BUILD=1
	)

target_compile_options(${RELEASE_TARGET}
	PUBLIC
	-Os
	)

target_include_directories(${RELEASE_TARGET}
	PUBLIC
	PRIVATE
	${SOS_INCLUDE_DIRECTORIES}
	)


option(BUILD_DEBUG "Build debug version of library" ON)
if(BUILD_DEBUG)
sos_sdk_library_target(DEBUG mbedtls "" debug v7m)
add_library(${DEBUG_TARGET} STATIC)
sos_sdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})
sos_sdk_library_add_arm_targets("${DEBUG_OPTIONS}")
endif()

sos_sdk_library_add_arm_targets("${RELEASE_OPTIONS}")

add_custom_target(
	${API_NAME}_format
	COMMAND /usr/local/bin/clang-format
	-i
	--verbose
	${FORMAT_LIST}
	)


