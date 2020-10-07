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
include( ${CMAKE_SOURCE_DIR}/${SOS_BUILD_CONFIG}.cmake )
