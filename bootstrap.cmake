cmake_minimum_required (VERSION 3.6)

#[[

cmake -P StratifyOS-mbedtls.cmake

]]#

if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
  set(SOS_TOOLCHAIN_CMAKE_PATH /Applications/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()
if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
  set(SOS_TOOLCHAIN_CMAKE_PATH C:/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
	set(SOS_TOOLCHAIN_CMAKE_PATH /StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
elseif()
	message(FATAL_ERROR "sl is not yet supportd on: " ${CMAKE_HOST_SYSTEM_NAME})
endif()

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-sdk.cmake)


#Pull or clone mbed-tls project
file(REMOVE mbedtls/include/mbedtls/config.h)
sos_sdk_clone_or_pull(./mbedtls https://github.com/ARMmbed/mbedtls.git ./)
sos_sdk_checkout(mbedtls "mbedtls-2.16")

#Need to replace the config file
file(COPY config/mbedtls/config.h DESTINATION mbedtls/include/mbedtls)

