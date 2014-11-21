#include "NetUtil.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <windef.h>

using namespace std;

//This should only really happen if we're using MinGW.
//Source: http://memset.wordpress.com/2010/10/09/inet_ntop-for-win32/
const char* inet_ntop(int af, const void* src, char* dst, int cnt){

    struct sockaddr_in srcaddr;

    memset(&srcaddr, 0, sizeof(struct sockaddr_in));
    memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));

    srcaddr.sin_family = af;
    if (WSAAddressToString((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0) {
        unsigned long rv = WSAGetLastError();
        cerr << "[ERROR: inet_ntop] WSAAddressToString() : " << rv << "\n";
        return NULL;
    }
    return dst;
}

int init_net() //This function makes me feel dirty.
{
    WORD requestedVer = MAKEWORD(2,2);
    WSADATA wsaData;
    int status = WSAStartup(requestedVer, &wsaData);
    if(status != 0)
    {
        return status;
    }
    if (LOBYTE(wsaData.wVersion) != 2)
    {
        status = 1;
    }
    return status;
}

int cleanup_net()
{
    WSACleanup();
    return 0;
}
