// this is the lock server
// the lock client has a similar interface

#ifndef lock_server_h
#define lock_server_h

#include <string>
#include "lock_protocol.h"
#include "lock_client.h"
#include "rpc.h"
#include <map>

using namespace std;

class lock_server {

 public:
  enum lock_status{
	free,locked
  };
 protected:
  int nacquire;
  map<lock_protocol::lockid_t,lock_status> mLocks;
  pthread_cond_t qready;
  pthread_mutex_t qlock;

 public:
  lock_server();
  ~lock_server() {};
  lock_protocol::status stat(int clt, lock_protocol::lockid_t lid, int &);
  lock_protocol::status acquire(int clt,lock_protocol::lockid_t lid,int &);
  lock_protocol::status release(int clt,lock_protocol::lockid_t lid,int &);
};

#endif 







