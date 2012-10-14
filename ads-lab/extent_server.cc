// the extent server implementation

#include "extent_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <ctime>

using namespace std;

extent_server::extent_server() {
    int r;
    put(0x00000001,"",r);
}


int extent_server::put(extent_protocol::extentid_t id, std::string buf, int &)
{
  // You fill this in for Lab 2.

    //Here I take every opetation on both file and file dir as the same, let the client to guarentee the correctness.

    extent_protocol::attr attribute;
    attribute.mtime = time(NULL);
    attribute.ctime = time(NULL);
    attribute.size = buf.size();
    if(mData.find(id)!=mData.end()){
        attribute.atime = mData[id].second.atime;
    }else{
        attribute.atime = time(NULL);
    }
    mData[id] = make_pair(buf,attribute);
    printf("extent_server:put %016llx ok,sz is %d\n",id,buf.size());
    return extent_protocol::OK;
}

int extent_server::get(extent_protocol::extentid_t id, std::string &buf)
{
  // You fill this in for Lab 2.
    if(mData.find(id)!=mData.end()){
        buf = mData[id].first;
        mData[id].second.atime = time(NULL);
        printf("get() id %016llx,sz %d\n",id,buf.size());
        return extent_protocol::OK;
    }else{
        buf = "";
        return extent_protocol::NOENT;
    }

}

int extent_server::getattr(extent_protocol::extentid_t id, extent_protocol::attr &a)
{
  // You fill this in for Lab 2.
    printf("getattr() id:%016llx\n",id);
    if(mData.find(id)!=mData.end()){
        extent_protocol::attr node = mData[id].second;
        a.size = node.size;
        a.atime = node.atime;
        a.mtime = node.mtime;
        a.ctime = node.ctime;
         printf("get() id %016llx,sz %d\n",id,a.size);
        return extent_protocol::OK;
    }
    printf("getattr(): not found...mData size:%d\n",mData.size());
    return extent_protocol::NOENT;
}

int extent_server::remove(extent_protocol::extentid_t id, int &)
{
  // You fill this in for Lab 2.

    //Here I take every opetation on both file and file dir as the same, let the client to guarentee the correctness.
    if(mData.find(id)!=mData.end()){
        return extent_protocol::NOENT;
    }
    mData.erase(id);
    return extent_protocol::OK;
}
