include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS})

SET(HEADERS spdylay_pq.h spdylay_int.h spdylay_map.h spdylay_queue.h   spdylay_buffer.h spdylay_frame.h spdylay_zlib.h   spdylay_session.h spdylay_helper.h spdylay_stream.h spdylay_int.h   spdylay_npn.h spdylay_gzip.h   spdylay_submit.h spdylay_outbound_item.h   spdylay_client_cert_vector.h   spdylay_net.h )

ADD_LIBRARY(spdylay STATIC spdylay_pq.c spdylay_map.c spdylay_queue.c   spdylay_buffer.c spdylay_frame.c spdylay_zlib.c   spdylay_session.c spdylay_helper.c spdylay_stream.c spdylay_npn.c   spdylay_submit.c spdylay_outbound_item.c   spdylay_client_cert_vector.c spdylay_gzip.c  ${HEADERS})

