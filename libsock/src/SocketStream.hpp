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

#include <sys/types.h> 
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h> 

#include <clews/core/CoreObject.hpp>

class SocketStream : public CoreObject
{
private:
    int mSocketFD, mBindSocketFD;
    uint32_t mPortNumber;
    uint32_t mBufferSize;
    bool mIsOpen;
    uint32_t mForeignIP;
    std::string mForeignIPStr;
    uint16_t mForeignPort;
public:
    SocketStream(uint32_t portNumber, int bufferSize);
    ~SocketStream();

    bool Open(std::string hostname);
	bool Close();

	bool Create();
	bool Destroy();
	
    std::string Read();
    std::string Readn(int bufferSize);
    std::string ReadLine();

    void Write(const std::string& msg);
    void WriteLine(const std::string& msg);

    int Listen();
    int Accept();

    int FD();
    void operator<<(std::string msg);
    void operator>>(std::string& msg);

    int BindToFD(int fd);
};

#endif
