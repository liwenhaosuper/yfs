// this is the lock server
// the lock client has a similar interface

#ifndef lock_server_h
#define lock_server_h

#include <string>
#include "lock_protocol.h"
#include <map>
#include "rpc/rpc.h"

using namespace std;

class lock_server {
 public:
	  enum lock_status{
		  free,locked
	  };
	  typedef unsigned long long sequence;
 protected:
  int nacquire;
  map<lock_protocol::lockid_t,lock_status> mLocks;
  pthread_cond_t qready;
  pthread_mutex_t qlock;
 public:
  lock_server();
  ~lock_server() {};
  lock_protocol::status stat(int clt, lock_protocol::lockid_t lid, lock_server::sequence seq, int &);
  lock_protocol::status acquire(int clt,lock_protocol::lockid_t lid,lock_server::sequence seq,int &);
  lock_protocol::status release(int clt,lock_protocol::lockid_t lid,lock_server::sequence seq,int &);
};

#endif 







