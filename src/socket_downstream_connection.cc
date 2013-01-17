#include "socket_downstream_connection.h"

#include "shrpx_client_handler.h"
#include "shrpx_upstream.h"
#include "shrpx_downstream.h"
#include "shrpx_config.h"
#include "shrpx_error.h"
#include "shrpx_http.h"
#include "util.h"

using namespace spdylay;



namespace shrpx {
// Gets called when DownstreamConnection is pooled in ClientHandler.
static void idle_eventcb(bufferevent *bev, short events, void *arg)
{
  SocketDownstreamConnection *dconn;
  dconn = reinterpret_cast<SocketDownstreamConnection*>(arg);
  if(events & BEV_EVENT_CONNECTED) {
    // Downstream was detached before connection established?
    // This may be safe to be left.
    if(ENABLE_LOG) {
      DCLOG(INFO, dconn) << "Idle connection connected?";
    }
    return;
  }
  if(events & BEV_EVENT_EOF) {
    if(ENABLE_LOG) {
      DCLOG(INFO, dconn) << "Idle connection EOF";
    }
  } else if(events & BEV_EVENT_TIMEOUT) {
    if(ENABLE_LOG) {
      DCLOG(INFO, dconn) << "Idle connection timeout";
    }
  } else if(events & BEV_EVENT_ERROR) {
    if(ENABLE_LOG) {
      DCLOG(INFO, dconn) << "Idle connection network error";
    }
  }
  ClientHandler *client_handler = dconn->get_client_handler();
  client_handler->remove_downstream_connection(dconn);
  delete dconn;
}

SocketDownstreamConnection::SocketDownstreamConnection
(ClientHandler *client_handler)
  : DownstreamConnection(client_handler),
    bev_(0),
    ioctrl_(0)    
{}


SocketDownstreamConnection::~SocketDownstreamConnection() noexcept{
   if(bev_) {
    bufferevent_disable(bev_, EV_READ | EV_WRITE);
    bufferevent_free(bev_);
  }
  // Downstream and DownstreamConnection may be deleted
  // asynchronously.
  if(downstream_) {
    downstream_->set_downstream_connection(0);
  }
}

int SocketDownstreamConnection::attach_downstream(Downstream *downstream){
  if(ENABLE_LOG) {
    DCLOG(INFO, this) << "Attaching to DOWNSTREAM:" << downstream;
  }
  Upstream *upstream = downstream->get_upstream();
  if(!bev_) {
    if(ENABLE_LOG) {
      DCLOG(INFO, this) << "Connecting to downstream server "<<downstream->getHostname()<<":"<<downstream->getDstPort();
    }
    event_base *evbase = client_handler_->get_evbase();
    bev_ = bufferevent_socket_new
      (evbase, -1,
       BEV_OPT_CLOSE_ON_FREE | BEV_OPT_DEFER_CALLBACKS);
	 
    int rv = bufferevent_socket_connect_hostname
      (bev_,client_handler_->get_ev_dns(),AF_INET,downstream->getHostname(),downstream->getDstPort());
	
    if(rv != 0) {
      bufferevent_free(bev_);
      bev_ = 0;
      return SHRPX_ERR_NETWORK;
    }

  }
  downstream->set_downstream_connection(this);
  downstream_ = downstream;
  ioctrl_.set_bev(bev_);

  bufferevent_setwatermark(bev_, EV_READ, 0, SHRPX_READ_WARTER_MARK);
  bufferevent_enable(bev_, EV_READ);
  bufferevent_setcb(bev_,
                    upstream->get_downstream_readcb(),
                    upstream->get_downstream_writecb(),
                    upstream->get_downstream_eventcb(), this);
  //TODO:要设置timeout吗？			
	return 0;
}
void SocketDownstreamConnection::detach_downstream(Downstream *downstream){
  if(ENABLE_LOG) {
    DCLOG(INFO, this) << "Detaching from DOWNSTREAM:" << downstream;
  }
  downstream->set_downstream_connection(0);
  downstream_ = 0;
  ioctrl_.force_resume_read();
  bufferevent_enable(bev_, EV_READ);
  bufferevent_setcb(bev_, 0, 0, idle_eventcb, this);
  // On idle state, just enable read timeout. Normally idle downstream
  // connection will get EOF from the downstream server and closed.
  bufferevent_set_timeouts(bev_,
                           &get_config()->downstream_idle_read_timeout,
                           &get_config()->downstream_write_timeout);
  client_handler_->pool_downstream_connection(this);
}

int SocketDownstreamConnection::push_request_headers(){return 0;}
int SocketDownstreamConnection::push_upload_data_chunk(const uint8_t *data, size_t datalen){return 0;}
int SocketDownstreamConnection::end_upload_data(){return 0;}

void SocketDownstreamConnection::pause_read(IOCtrlReason reason){}
bool SocketDownstreamConnection::resume_read(IOCtrlReason reason){return true;}
void SocketDownstreamConnection::force_resume_read(){}

bool SocketDownstreamConnection::get_output_buffer_full(){return true;}

int SocketDownstreamConnection::on_read(){return 0;}
int SocketDownstreamConnection::on_write(){return 0;}
int SocketDownstreamConnection::on_upstream_write(){ return 0;}

bufferevent* SocketDownstreamConnection::get_bev(){return bev_;}
	
}