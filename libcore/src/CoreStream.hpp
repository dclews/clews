#ifndef CORE_STREAM_HPP
#define CORE_STREAM_HPP

#include "CoreStreamBuf.hpp"

class CoreStream : public std::ostream
{
private:
   bool mEnabled;
   CoreStreamBuffer mStreamBuf;
public:
	CoreStream(std::ostream& target, bool enable);

	void SetPrefix(std::string prefix);
	void ClearPrefix();
	void Enable(bool doEnable);
	bool IsEnabled();
};

#endif
