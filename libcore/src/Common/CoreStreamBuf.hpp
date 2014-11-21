#ifndef CORE_STREAM_BUF_HPP
#define CORE_STREAM_BUF_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <iostream>
#include <sstream>

class CoreStreamBuffer : public std::stringbuf
{
private:
		std::ostream& mOutputStream;
		bool mEnabled;
		std::string mPrefix;

public:
		CoreStreamBuffer(std::ostream& str, bool enabled);
		void SetPrefix(std::string prefix);
		void ClearPrefix();
		void Enable(bool doEnable);
		bool IsEnabled();
		int sync();
};

#endif
