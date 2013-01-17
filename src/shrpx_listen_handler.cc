/*
 * Spdylay - SPDY Library
 *
 * Copyright (c) 2012 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "shrpx_listen_handler.h"

#include <unistd.h>
#include <pthread.h>

#include <cerrno>

#include <event2/bufferevent_ssl.h>

#include "shrpx_client_handler.h"
#include "shrpx_ssl.h"
#include "shrpx_worker.h"
#include "shrpx_config.h"

namespace shrpx {

ListenHandler::ListenHandler(event_base *evbase)
  : evbase_(evbase),
    ssl_ctx_(ssl::create_ssl_context()),
    worker_round_robin_cnt_(0),
    workers_(0),
    num_worker_(0),
    spdy_(0)
{}

ListenHandler::~ListenHandler()
{}

/**
 * 当accept到新连接的时候调用此方法
 */
int ListenHandler::accept_connection(evutil_socket_t fd,
                                     sockaddr *addr, int addrlen)
{
  if(ENABLE_LOG) {
    LLOG(INFO, this) << "Accepted connection. fd=" << fd;
  }
  
  ssl::accept_ssl_connection(evbase_, ssl_ctx_, fd, addr, addrlen);  
  return 0;
}

event_base* ListenHandler::get_evbase() const
{
  return evbase_;
}



} // namespace shrpx
