#pragma once

#include "shrpx.h"

#include <event.h>
#include <event2/bufferevent.h>


#include "shrpx_downstream_connection.h"
#include "shrpx_io_control.h"

namespace shrpx {

  class SocketDownstreamConnection : public DownstreamConnection {
  public:
    SocketDownstreamConnection(ClientHandler *client_handler);
    virtual ~SocketDownstreamConnection() noexcept;
    virtual int attach_downstream(Downstream *downstream);
    virtual void detach_downstream(Downstream *downstream);

    virtual int push_request_headers();
    virtual int push_upload_data_chunk(const uint8_t *data, size_t datalen);
    virtual int end_upload_data();

    virtual void pause_read(IOCtrlReason reason);
    virtual bool resume_read(IOCtrlReason reason);
    virtual void force_resume_read();

    virtual bool get_output_buffer_full();

    virtual int on_read();
    virtual int on_write();
    virtual int on_upstream_write();

    bufferevent* get_bev();
  private:
    bufferevent *bev_;
    IOControl ioctrl_;
  };

} // namespace shrpx
