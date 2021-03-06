// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

lock_server::lock_server():
  nacquire (0)
{
	memset(&qlock,0,sizeof(qlock));
	memset(&qready,0,sizeof(qready));
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
  if(mLocks.count(lid)==1){
	  r = lock_server::locked;
  }else{
	  r = lock_server::free;
  }
  printf("stat request from clt %d,%lld\n", clt,lid);
  return ret;
}


lock_protocol::status
lock_server::acquire(int clt, lock_protocol::lockid_t lid,int &r)
{
	//printf("acquire request from clt %d,%lld\n", clt,lid);
	pthread_mutex_lock(&qlock);
	if(mLocks.count(lid)==0){
		mLocks[lid] = lock_server::locked;
		pthread_mutex_unlock(&qlock);
	}else if(mLocks[lid]!=lock_server::locked){
		mLocks[lid] = lock_server::locked;
		pthread_mutex_unlock(&qlock);
	}else{
		nacquire++;
		//printf("lock %d,%lld\n",nacquire,lid);
		//pthread_mutex_lock(&qlock);
		//struct timespec tsp;
		//struct timeval now;
		//gettimeofday(&now,NULL);
		//tsp.tv_sec = now.tv_sec+3;
		//tsp.tv_nsec = now.tv_usec*1000;
		while(mLocks[lid]==lock_server::locked){
			//pthread_cond_timedwait(&qready,&qlock,&tsp);
			pthread_cond_wait(&qready,&qlock);
		}
		mLocks[lid] = lock_server::locked;
		pthread_mutex_unlock(&qlock);
		nacquire--;
		//printf("lock %d,%lld --\n",nacquire,lid);
	}
	r = nacquire;
	return lock_protocol::OK;
}
lock_protocol::status
lock_server::release(int clt, lock_protocol::lockid_t lid, int &r)
{
	//printf("release request from clt %d,%lld\n", clt,lid);
	if(mLocks.count(lid)==0||mLocks[lid]!=lock_server::locked){
		r = nacquire;
		return lock_protocol::OK;
	}
	//printf("release lock %lld\n",lid);
	mLocks[lid] = lock_server::free;
	if(nacquire){
		pthread_cond_signal(&qready);
	}
	r = nacquire;
	return lock_protocol::OK;
}

