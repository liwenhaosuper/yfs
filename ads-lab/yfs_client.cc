// yfs client.  implements FS operations using extent and lock server
#include "yfs_client.h"
#include "extent_client.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


yfs_client::yfs_client(std::string extent_dst, std::string lock_dst)
{
  ec = new extent_client(extent_dst);
  printf("yfs_client:create extent_client OK\n");
}

yfs_client::inum
yfs_client::n2i(std::string n)
{
  std::istringstream ist(n);
  unsigned long long finum;
  ist >> finum;
  return finum;
}

std::string
yfs_client::filename(inum inum)
{
  std::ostringstream ost;
  ost << inum;
  return ost.str();
}

bool
yfs_client::isfile(inum inum)
{
  if(inum & 0x80000000)
    return true;
  return false;
}

bool
yfs_client::isdir(inum inum)
{
    return ! isfile(inum);
}


int
yfs_client::getfile(yfs_client::inum inum, fileinfo &fin)
{
  int r = OK;

  printf("getfile %016llx\n", inum);
  extent_protocol::attr a;
  if (ec->getattr(inum, a) != extent_protocol::OK) {
    r = IOERR;
    goto release;
  }

  fin.atime = a.atime;
  fin.mtime = a.mtime;
  fin.ctime = a.ctime;
  fin.size = a.size;
  printf("getfile %016llx -> sz %llu\n", inum, fin.size);

 release:
  a.size = 0;
  return r;
}

int yfs_client::getfiledata(yfs_client::inum inum, size_t sz, off_t offset, std::string &data)
{
    if(!isfile(inum)){  //not a file!
        printf("%016llx is not a file!\n",inum);
        return IOERR;
    }
    int r = OK;
    printf("getfiledata %016llx of %d begin with %d\n",inum,sz,offset);
    r = ec->get(inum,data);
    if(r!=extent_protocol::OK){
        printf("getfiledata %016llx error!\n",inum);
        data="";
        return r;
    }
    if(sz>0&&offset>=0){
        data = data.substr(offset,sz);
    }
    printf("getfiledata %016llx : sz %u\n",inum, data.size());
    return r;
}

int
yfs_client::getdir(yfs_client::inum inum, dirinfo &din)
{

  int r = OK;
  printf("getdir %016llx\n", inum);
  extent_protocol::attr a;
  if (ec->getattr(inum, a) != extent_protocol::OK) {
    r = IOERR;
    goto release;
  }
  din.atime = a.atime;
  din.mtime = a.mtime;
  din.ctime = a.ctime;

 release:
  return r;
}

int yfs_client::getdirdata(yfs_client::dirent& dir)
{
    if(!isdir(dir.inum)){  //not a dir!
        printf("%016llx is not a dir!\n",dir.inum);
        return IOERR;
    }
    int r = OK;
    printf("getdirdata %016llx\n", dir.inum);
    //TODO: to be continue
    r = ec->get(dir.inum,dir.name);
    if(r!=extent_protocol::OK){
      if(r==extent_protocol::NOENT){
          //not exist
          printf("getdirdata %016llx not exists\n", dir.inum);
      }

    }
    else printf("getdirdata %016llx : sz %u\n",dir.inum, dir.name.size());
    return r;
}

int yfs_client::put(yfs_client::inum id, std::string &buf)
{
    int r = OK;
    printf("put %016llx\n", id);
    //TODO: to be continue
    if(ec->put(id,buf)!=extent_protocol::OK){
      r = IOERR;
      //std::cout.flush();
      //std::cout<<"put "<<id<<" io error\n";
      return r;
    }
    //printf("put %016llx : sz %u,data:%s\n",id, buf.size(),buf.c_str());
    return r;
}

int yfs_client::remove(yfs_client::inum id)
{
    int r = OK;
    printf("remove %016llx\n", id);
    //TODO: to be continue
    if(ec->remove(id)!=extent_protocol::OK){
      r = IOERR;
    }
    return r;
}



