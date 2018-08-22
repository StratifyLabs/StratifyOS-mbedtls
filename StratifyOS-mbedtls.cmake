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
