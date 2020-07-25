cmake_minimum_required (VERSION 3.6)

#[[

cmake -P StratifyOS-mbedtls.cmake

]]#

# Grab the SDK location
if(NOT DEFINED SOS_SDK_PATH)
	if(DEFINED ENV{SOS_SDK_PATH})
		set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /Applications/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH C:/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /StratifyLabs-SDK)
	endif()
endif()
if(NOT DEFINED SOS_SDK_PATH)
	message(FATAL_ERROR "Please set environment variable SOS_SDK_PATH to location of the StratifyLabs-SDK directory")
endif()
set(SOS_TOOLCHAIN_CMAKE_PATH ${SOS_SDK_PATH}/Tools/gcc/arm-none-eabi/cmake)

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-sdk.cmake)


#Pull or clone mbed-tls project
file(REMOVE mbedtls/include/mbedtls/config.h)
sos_sdk_clone_or_pull(./mbedtls https://github.com/ARMmbed/mbedtls.git ./)
sos_sdk_checkout(mbedtls "mbedtls-2.16")

#Need to replace the config file
file(COPY config/mbedtls/config.h DESTINATION mbedtls/include/mbedtls)

