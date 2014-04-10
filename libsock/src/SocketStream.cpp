#include "SocketStream.hpp"
#include <arpa/inet.h>

using namespace std;

SocketStream::SocketStream(uint32_t portNumber, int bufferSize) : CoreObject("SocketStream"), mPortNumber(portNumber),
    mBufferSize(bufferSize), mIsOpen(false)
{
    DebugOut() << "PortNumber: " << mPortNumber << endl;
}
SocketStream::~SocketStream()
{
    DebugOut() << "~SocketStream()" << endl;
	Close();
}
bool SocketStream::Open(string hostname)
{
    SetPrintPrefix(__func__, FUNC_PRINT);

    StandardOut() << "Opening Socket: " << mPortNumber << hostname << ":" << mPortNumber << endl << endl;

    bool success = true;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    mSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (mSocketFD > 0)
    {
        server = gethostbyname(hostname.c_str());
        if (server != NULL)
        {
            memset((char*) &serv_addr, 0, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;

            memcpy((char*) &serv_addr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
            serv_addr.sin_port = htons(mPortNumber);

            if (connect(mSocketFD,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
            {
                ErrorOut() << "Failed to connect to host: " << hostname << endl;
                success = false;
            }
        }
        else
        {
            ErrorOut() << "Failed to find host: " << hostname << endl;
            success = false;
        }
    }
    else
	{
        ErrorOut() << "Failed to open socket." << endl;
        success = false;
    }

    ClearPrintPrefix();
    mIsOpen = success;
    return success;
}
bool SocketStream::Close()
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    StandardOut() << "Closing Socket: " << mPortNumber << endl;

    if(mIsOpen)	close(mSocketFD);
    mIsOpen = false;

    ClearPrintPrefix();
    return true;
}

bool SocketStream::Create()
{
    SetPrintPrefix(__func__, FUNC_PRINT);

    bool status = true;
    struct sockaddr_in serv_addr;

    StandardOut() << "Creating Socket on port " << mPortNumber << endl;

    mBindSocketFD = socket(AF_INET, SOCK_STREAM, 0);
     
    if (mBindSocketFD < 0)
	{ 
       ErrorOut() << "Failed to open socket." << endl;
	   return false;
	}
    
    memset((char*) &serv_addr, 0, sizeof(serv_addr));
    
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(mPortNumber);

    StandardOut() << "Binding to Socket " << mPortNumber << endl;

    if (bind(mBindSocketFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
       ErrorOut() << "Failed to bind to socket." << endl;
       status = false;
	}

    ClearPrintPrefix();
    return status;
}
int SocketStream::Listen()
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    StandardOut() << "Listening for connections..." << endl;
    listen(mBindSocketFD,5);
    ClearPrintPrefix();
    return 0;
}
int SocketStream::Accept()
{
    SetPrintPrefix(__func__, FUNC_PRINT);

    struct sockaddr_in cli_addr;
    socklen_t clilen;
    clilen = sizeof(cli_addr);

    mSocketFD = accept(mBindSocketFD, (struct sockaddr *) &cli_addr, &clilen);
	
    mForeignIP = ntohl(cli_addr.sin_addr.s_addr);
    mForeignPort = ntohs((uint16_t) cli_addr.sin_port);

    char buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &mForeignIP, buffer, INET_ADDRSTRLEN);
    mForeignIPStr = buffer;

    StandardOut() << "Got new client: " << mForeignIPStr << endl;

    if (mSocketFD < 0)
	{
        ErrorOut() << "Failed to accept socket connection." << endl;
	}
    ClearPrintPrefix();
    return mSocketFD;
}
bool SocketStream::Destroy()
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    ErrorOut() << "Destroying Socket." << endl;

    close(mSocketFD);
    close(mBindSocketFD);

    ClearPrintPrefix();
	return true;
}

string SocketStream::Read()
{
    return Readn(mBufferSize);
}


string SocketStream::Readn(int bufferSize)
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    char buffer[bufferSize];
    int n = read(mSocketFD,buffer,bufferSize);
    if (n < 0)
    {
        ErrorOut() << "Failed to read from socket." << endl;
    }

    DebugOut() << buffer << endl;
    ClearPrintPrefix();
    return string(buffer);
}

string SocketStream::ReadLine()
{
    string s;

    do
    {
        s = Readn(2);
    }
    while(s.at(s.length()-1) != '\n');

    return s;
}

void SocketStream::Write(const std::string& msg)
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    DebugOut() << "[W->" << mForeignIPStr << "] " << msg << endl;
    write(mSocketFD, (const void*) msg.c_str(), msg.length());
    ClearPrintPrefix();
}
void SocketStream::WriteLine(const std::string& msg)
{
    std::string lineMsg = msg+"\n";
    Write(lineMsg);
}

void SocketStream::operator<<(std::string msg)
{
    Write(msg);
}

void SocketStream::operator>>(string& msg)
{
    msg = Read();
}

int SocketStream::BindToFD(int fd)
{
    return dup2(mSocketFD, fd);
}

int SocketStream::FD()
{
    return mSocketFD;
}
