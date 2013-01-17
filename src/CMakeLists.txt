cmake_minimum_required (VERSION 2.8) 
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS})

add_definitions(-DUNICODE -D_UNICODE -DHAVE_CONFIG_H )


add_executable(shrpx  shrpx_config.cc shrpx_config.h shrpx.cc shrpx.h shrpx_error.h shrpx_listen_handler.cc shrpx_listen_handler.h shrpx_client_handler.cc shrpx_client_handler.h shrpx_upstream.h shrpx_spdy_upstream.cc shrpx_spdy_upstream.h shrpx_downstream_queue.cc shrpx_downstream_queue.h shrpx_downstream.cc shrpx_downstream.h shrpx_downstream_connection.cc shrpx_downstream_connection.h shrpx_http_downstream_connection.cc shrpx_http_downstream_connection.h shrpx_log.cc shrpx_log.h shrpx_http.cc shrpx_http.h shrpx_io_control.cc shrpx_io_control.h shrpx_ssl.cc shrpx_ssl.h shrpx_thread_event_receiver.cc shrpx_thread_event_receiver.h shrpx_worker.cc shrpx_worker.h shrpx_accesslog.cc shrpx_accesslog.h http-parser/http_parser.c http-parser/http_parser.h util.cc spdylay_ssl.cc util.h spdylay_ssl.h spdylay_config.h base64.h base64.cpp login_helper.h login_helper.cpp socket_downstream_connection.h socket_downstream_connection.cc)
target_link_libraries(shrpx spdylay event event_openssl  ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
