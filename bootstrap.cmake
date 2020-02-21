cmake_minimum_required (VERSION 3.6)

#[[

cmake -P StratifyOS-mbedtls.cmake

]]#

if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
set(SOS_TOOLCHAIN_CMAKE_PATH /Applications/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()
if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
  set(SOS_TOOLCHAIN_CMAKE_PATH C:/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-sdk.cmake)


#Pull or clone mbed-tls project
sos_sdk_clone_or_pull(./mbedtls https://github.com/ARMmbed/mbedtls.git ./)
sos_sdk_checkout(mbedtls "mbedtls-2.16")

#Need to rename mbedtls/include/mbedtls/config.h to mbedtls/include/mbedtls/config_notused_renamed.h
if(EXISTS mbedtls/include/mbedtls/config.h)
	file(RENAME mbedtls/include/mbedtls/config.h mbedtls/include/mbedtls/config_notused_renamed.h)
endif()
