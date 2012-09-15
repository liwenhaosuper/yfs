// RPC stubs for clients to talk to lock_server

#include "lock_client.h"
#include "rpc/rpc.h"
#include <arpa/inet.h>

#include <sstream>
#include <iostream>
#include <stdio.h>


lock_client::sequence lock_client::mSeq = 1000;

lock_client::lock_client(std::string dst)
{
  sockaddr_in dstsock;
  make_sockaddr(dst.c_str(), &dstsock);
  cl = new rpcc(dstsock);
  if (cl->bind() < 0) {
    printf("lock_client: call bind\n");
  }
}

lock_client::sequence lock_client::generateSequence() {
	mSeq++;
	return mSeq;
}

int
lock_client::stat(lock_protocol::lockid_t lid)
{
  sequence seq = generateSequence();
  int r;
  int ret = cl->call(lock_protocol::stat, cl->id(), lid, seq,r);
  assert (ret == lock_protocol::OK);
  return r;
}

lock_protocol::status
lock_client::acquire(lock_protocol::lockid_t lid)
{
	sequence seq = generateSequence();
	int r;
	int ret = cl->call(lock_protocol::acquire,cl->id(),lid,seq,r);
	assert(ret==lock_protocol::OK);
	return r;
}

lock_protocol::status
lock_client::release(lock_protocol::lockid_t lid)
{
	sequence seq = generateSequence();
	int r;
	int ret = cl->call(lock_protocol::release,cl->id(),lid,seq,r);
	assert(ret==lock_protocol::OK);
	return r;
}

