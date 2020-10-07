cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/Tools/gcc/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

set(SOS_NAME mbedtls)
project(StratifyOS-mbedtls C)


set(SOS_DEFINITIONS IS_LOCAL_BUILD=1)
set(SOS_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/config/mbedtls mbedtls/include ${CMAKE_SOURCE_DIR})

install(DIRECTORY mbedtls/include/mbedtls DESTINATION include)
install(FILES mbedtls_api.h mbedtls_link_config.h mbedtls_sos_config.h DESTINATION include)
#include( ${CMAKE_SOURCE_DIR}/${SOS_BUILD_CONFIG}.cmake )


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
	net_sockets.c
	timing_alt.h
	threading.c)

set(SOS_OPTION kernel)
set(SOS_DEFINITIONS ${SOS_DEFINITIONS} -DHAVE_LWIP_SOCKETS_H)

if(SOS_IS_ARM)
	set(LIB_OPTION kernel)
	list(APPEND PRIVATE_SOURCELIST mbedtls_sos_config.h)
else()
	list(APPEND PRIVATE_SOURCELIST mbedtls_link_config.h)
endif()

sos_sdk_library_target(RELEASE mbedtls "${LIB_OPTION}" release ${SOS_ARCH})

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
sos_sdk_library_target(DEBUG mbedtls "${LIB_OPTION}" debug ${SOS_ARCH})
add_library(${DEBUG_TARGET} STATIC)
sos_sdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})
sos_sdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${SOS_ARCH})
endif()

sos_sdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${SOS_ARCH})

add_custom_target(
	${API_NAME}_format
	COMMAND /usr/local/bin/clang-format
	-i
	--verbose
	${FORMAT_LIST}
	)
