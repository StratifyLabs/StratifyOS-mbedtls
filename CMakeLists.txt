cmake_minimum_required (VERSION 3.6)


if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
  message(STATUS "Load Darwin Toolchain for arm")
  set(SOS_TOOLCHAIN_CMAKE_PATH /Applications/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()
if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
  message(STATUS "Load Windows Toolchain for arm")
  set(SOS_TOOLCHAIN_CMAKE_PATH C:/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-variables.cmake)

if( ${SOS_BUILD_CONFIG} STREQUAL arm )
  set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-toolchain.cmake)
elseif( ${SOS_BUILD_CONFIG} STREQUAL link )
  set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/link-toolchain.cmake)
endif()

set(SOS_NAME mbedtls)
project(${SOS_NAME} CXX C ASM)

set(SOS_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/config ${CMAKE_SOURCE_DIR}/config/mbedtls mbedtls/include ${CMAKE_SOURCE_DIR})
install(DIRECTORY mbedtls/include/mbedtls DESTINATION include)
install(FILES mbedtls_api.h link_config.h sos_config.h DESTINATION include)
include( ${CMAKE_SOURCE_DIR}/${SOS_BUILD_CONFIG}.cmake )
