#ifndef CORE_OBJECT_HPP
#define CORE_OBJECT_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "CoreStream.hpp"

enum PrintTypes
{
		STD_PRINT = 0,
		FUNC_PRINT = 1
};

class CoreObject
{
private:
		std::string mTypeID;
		std::string mTypePrefix;
		std::string mPrefix;

		CoreStream mSTD;
		CoreStream mDebug;
		CoreStream mWarn;
		CoreStream mError;
		std::vector< std::pair<std::string, PrintTypes> > mPrefixStack;

		static const char* mSTDPrefix;
		static const char* mWarningPrefix;
		static const char* mDebugPrefix;
		static const char* mErrorPrefix;
public:
		CoreObject(std::string typeID);
		~CoreObject();

		CoreStream& StandardOut();
		CoreStream& ErrorOut();
		CoreStream& WarningOut();
		CoreStream& DebugOut();

		void SetPrintPrefix(std::string prefix, PrintTypes type=STD_PRINT);
		void ClearPrintPrefix();
		std::string TypeID();

		void PushPrintPrefix(std::string prefix, PrintTypes type);
		void PopPrintPrefix();
};

#endif
