#include "CoreStreamBuf.hpp"

CoreStreamBuffer::CoreStreamBuffer(std::ostream& target, bool enable = true) : mOutputStream(target), mEnabled(enable) {}

void CoreStreamBuffer::SetPrefix(std::string prefix)
{
		//std::cout << "CoreStreamBuf::SetPrefix('" << prefix << "'')" << std::endl;

		mPrefix = prefix;
}

void CoreStreamBuffer::ClearPrefix()
{
		mPrefix = "";
}
void CoreStreamBuffer::Enable(bool doEnable)
{
//    std::cout << "CoreStreamBuf::Enable(" << doEnable << ")" << std::endl;
	mEnabled = doEnable;
}

bool CoreStreamBuffer::IsEnabled()
{
	return mEnabled;
}

// When we sync the stream with the output.
// 1) Output Plop then the buffer
// 2) Reset the buffer
// 3) flush the actual output stream we are using.
int CoreStreamBuffer::sync()
{
		//std::cout << "CoreStreamBuffer::sync()" << std::endl;
		if(mEnabled)
		{
				//std::cout << "PRINTING. Prefix is: " << mPrefix << std::endl;
				mOutputStream << mPrefix << str();
		}
		str("");
		mOutputStream.flush();
		//std::cout << "CoreStreamBuffer::sync[]" << std::endl;
		return 0;
}
