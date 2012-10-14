// this is the extent server

#ifndef extent_server_h
#define extent_server_h

#include <string>
#include <map>
#include "extent_protocol.h"
#include <time.h>



class extent_server {

 public:
  extent_server();
  int put(extent_protocol::extentid_t id, std::string, int &);
  int get(extent_protocol::extentid_t id, std::string &);
  int getattr(extent_protocol::extentid_t id, extent_protocol::attr &);
  int remove(extent_protocol::extentid_t id, int &);
 private:
  //(inum,{data,attr})
  std::map<extent_protocol::extentid_t, std::pair<std::string,extent_protocol::attr> > mData;
};





#endif 







