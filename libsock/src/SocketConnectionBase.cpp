#include "SocketConnectionBase.hpp"

using namespace std;

SocketConnectionBase::SocketConnectionBase(string typeID, size_t bufferSize) : CoreObject(typeID), mBufferSize(bufferSize), mIsOpen(false) {}

string SocketConnectionBase::Readn(uint32_t bufferSize)
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    char buffer[bufferSize];
    int n = read(mConnectionFD,buffer,bufferSize);

    if (n < 0)
    {
        ErrorOut() << "Failed to read from socket." << endl;
    }

    string strBuffer(buffer);
    DebugOut() << "[R<-" << mForeignIPStr << "]" << strBuffer << endl;
    ClearPrintPrefix();
    return strBuffer;
}
string SocketConnectionBase::Read()
{
    return Readn(mBufferSize);
}
void SocketConnectionBase::operator>>(string& msg)
{
    msg = Read();
}

void SocketConnectionBase::Write(const std::string& msg)
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    DebugOut() << "[W->" << mForeignIPStr << "] " << msg << endl;
    write(mConnectionFD, (const void*) msg.c_str(), msg.length());
    ClearPrintPrefix();
}
void SocketConnectionBase::WriteLine(const std::string& msg)
{
    std::string lineMsg = msg+"\n";
    Write(lineMsg);
}
void SocketConnectionBase::operator<<(std::string msg)
{
    Write(msg);
}

bool SocketConnectionBase::SocketConnectionBase::IsOpen()
{
    return mIsOpen;
}

void SocketConnectionBase::SocketConnectionBase::Close()
{
    if(mIsOpen)	close(mConnectionFD);
}

int SocketConnectionBase::FD()
{
    return mConnectionFD;
}
int SocketConnectionBase::BindToFD(int fd)
{
    return dup2(mConnectionFD, fd);
}
