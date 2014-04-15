#include "SocketClient.hpp"

#include <netinet/in.h>
#include <netdb.h>

using namespace std;

SocketClient::SocketClient(size_t bufferSize) : SocketConnectionBase("SocketClient", bufferSize)
{
}
bool SocketClient::Open(string hostname, uint32_t port)
{
    SetPrintPrefix(__func__, FUNC_PRINT);

    mConnectionFD = socket(AF_INET, SOCK_STREAM, 0);
    mForeignPort = port;
    if(mConnectionFD >= 0)
    {
        struct hostent* server = gethostbyname(hostname.c_str());
        if (server != NULL)
        {
            struct sockaddr_in serv_addr;
            memset((char*) &serv_addr, 0, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;

            memcpy((char*) &serv_addr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
            serv_addr.sin_port = htons(mForeignPort);

            if (connect(mConnectionFD,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) >= 0)
            {
                mIsOpen = true;
            }
            else
            {
                ErrorOut() << "Failed to connect to host: " << hostname << endl;
            }
        }
    }

    ClearPrintPrefix();
    return mIsOpen;
}
