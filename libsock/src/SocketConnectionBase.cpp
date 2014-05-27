#include "SocketConnectionBase.hpp"

using namespace std;

SocketConnectionBase::SocketConnectionBase(string typeID, size_t bufferSize) : CoreObject(typeID), mBufferSize(bufferSize), mIsOpen(false) {}

string SocketConnectionBase::Readn(uint32_t bufferSize)
{
	PushPrintPrefix(__func__, FUNC_PRINT);
	DebugOut() << "Acquiring Mutex" << endl;
	mtx.lock();
		char buffer[bufferSize];
		int n = read(mConnectionFD,buffer,bufferSize);

		if (n < 0)
		{
				ErrorOut() << "Failed to read from socket." << endl;
		}

		string strBuffer(buffer, n);
		DebugOut() << "[R<-" << mForeignIPStr << "]" << strBuffer << endl;
	mtx.unlock();
	PopPrintPrefix();
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
	PushPrintPrefix(__func__, FUNC_PRINT);
	DebugOut() << "Acquiring Mutex" << endl;
	mtx.lock();
		DebugOut() << "[W->" << mForeignIPStr << "] " << msg << endl;
		//Write the cstr equivalent of the message with an extra space for the terminating null character.
		write(mConnectionFD, (const void*) msg.c_str(), msg.length()+1);
	mtx.unlock();
	PopPrintPrefix();
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
string SocketConnectionBase::ForeignIP()
{
	return mForeignIPStr;
}
