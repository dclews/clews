#ifndef SOCKET_STREAM_H
#define SOCKET_STREAM_H

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <fcntl.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#include <sys/types.h> 
#include <sys/socket.h>

#include <netinet/in.h>
#include "SocketConnection.hpp"
#include <clews/core/CoreObject.hpp>

class Socket : public CoreObject
{
private:
    int mSocketFD;
    uint32_t mPortNumber;
    uint32_t mBufferSize;
    bool mIsOpen;
    std::vector<SocketConnection*> mConnections;
public:
    Socket(uint32_t portNumber, int bufferSize);
    ~Socket();

    SocketConnection* Open(std::string hostname);

	bool Create();
	bool Destroy();
	
    bool Listen();
    SocketConnection* Accept();

    int FD();


    int BindToFD(int fd);
};

#endif
