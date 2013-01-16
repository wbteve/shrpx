cmake_minimum_required (VERSION 2.6) 
project (shrpx)
find_package (Threads)
find_package (OpenSSL)
find_package (ZLIB)
ENABLE_TESTING()


set(CMAKE_CXX_FLAGS "--std=c++11 -pthread")
include (CheckIncludeFiles)
include (CheckIncludeFileCXX)
include (CheckCXXSourceCompiles)
check_include_file_cxx (inttypes.h HAVE_INTTYPES_H)
check_include_file_cxx (arpa/inet.h HAVE_ARPA_INET_H)
check_include_file_cxx (dlfcn.h HAVE_DLFCN_H)
check_include_file_cxx (memory.h HAVE_MEMORY_H)
check_include_file_cxx (netinet/in.h HAVE_NETINET_IN_H)
check_include_file_cxx (pwd.h HAVE_PWD_H)
check_include_file_cxx (stddef.h HAVE_STDDEF_H)
check_include_file_cxx (stdint.h HAVE_STDINT_H)
check_include_file_cxx (stdlib.h HAVE_STDLIB_H)
check_include_file_cxx (strings.h HAVE_STRINGS_H)
check_include_file_cxx (string.h HAVE_STRING_H)
check_include_file_cxx (sys/stat.h HAVE_SYS_STAT_H)
check_include_file_cxx (sys/types.h HAVE_SYS_TYPES_H)
check_include_file_cxx (time.h HAVE_TIME_H)
check_include_file_cxx (unistd.h HAVE_UNISTD_H)
check_include_file_cxx (winsock2.h HAVE_WINSOCK2_H)


configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
 )
ADD_SUBDIRECTORY(spdylay) 
ADD_SUBDIRECTORY(src)
