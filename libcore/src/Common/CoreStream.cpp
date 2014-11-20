#include "CoreStream.hpp"

CoreStream::CoreStream(std::ostream& target, bool enable) : mStreamBuf(target, enable), std::ostream(&mStreamBuf)
{
}
void CoreStream::SetPrefix(std::string prefix)
{
		mStreamBuf.SetPrefix(prefix);
}
void CoreStream::ClearPrefix()
{
		mStreamBuf.ClearPrefix();
}
void CoreStream::Enable(bool doEnable)
{
//    std::cout << "CoreStream::Enable(" << doEnable << ")" << std::endl;
		mStreamBuf.Enable(doEnable);
}
bool CoreStream::IsEnabled()
{
		return mStreamBuf.IsEnabled();
}


