#ifndef SOCKETCONNECTION_HPP
#define SOCKETCONNECTION_HPP

#include <string>
#include <string.h>
#include <netdb.h>
#include "SocketConnectionBase.hpp"
#include <arpa/inet.h>

class SocketConnection : public SocketConnectionBase
{
private:
    int mSocketFD;

public:
    SocketConnection(int socketFD, size_t bufferSize);
    ~SocketConnection();

    bool Open(std::string hostname);
    void Close();
    bool Accept();
};

#endif // SOCKETCONNECTION_HPP
