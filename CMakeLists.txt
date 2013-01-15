cmake_minimum_required (VERSION 2.6) 
project (shrpx)
find_package (Threads)
find_package (OpenSSL)
find_package (ZLIB)
ENABLE_TESTING()


set(CMAKE_CXX_FLAGS "--std=c++11 -pthread")

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
 )
 
ADD_SUBDIRECTORY(src)
