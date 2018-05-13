#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

namespace common {
namespace logging {

static const std::string FATAL_TAG = "[FATAL  ] ";
static const std::string ERROR_TAG = "[ERROR  ] ";
static const std::string WARNING_TAG = "[WARNING] ";
static const std::string INFO_TAG = "[INFO   ] ";
static const std::string DEBUG_TAG = "[DEBUG  ] ";
static const std::string ASSERT_TAG = "[ASSERT ] ";
static const int TAG_WIDTH = 10;

//http://stackoverflow.com/a/29752943
void replaceAll( std::string& source, const std::string& from, const std::string& to )
{
    std::string newString;
    newString.reserve( source.length() );  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while( std::string::npos != ( findPos = source.find( from, lastPos )))
    {
        newString.append( source, lastPos, findPos - lastPos );
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr( lastPos );

    source.swap( newString );
}

inline
std::string resetLinebreaks( std::string msg )
{
   std::string newline = "\n";
   newline.append( TAG_WIDTH, ' ' );
   replaceAll(msg, "\n", newline);
	return msg;
}

inline
std::string createLog( const std::string & tag, const std::string & msg,
                       const std::string & caller, const int line )
{
   std::stringstream log;
   log << tag;
   if (!caller.empty())
   {
   	log << "File: " << caller << ":" << line << "\n";
	}
	log << msg;
   return resetLinebreaks( log.str() );
}

inline
void log( const std::string& msg )
{
	std::cout << msg << std::endl;
}

#define LOG_FATAL(msg){\
	std::stringstream ss;\
	ss << msg;\
	common::logging::log( common::logging::createLog( common::logging::FATAL_TAG, ss.str(), __FILE__, __LINE__ ));\
}
#define LOG_ERROR(msg){\
	std::stringstream ss;\
	ss << msg;\
	common::logging::log( common::logging::createLog( common::logging::ERROR_TAG, ss.str(), __FILE__, __LINE__ ));\
}
#define LOG_WARNING(msg){\
	std::stringstream ss;\
	ss << msg;\
	common::logging::log( common::logging::createLog( common::logging::WARNING_TAG, ss.str(), __FILE__, __LINE__ ));\
}
#define LOG_INFO(msg){\
	std::stringstream ss;\
	ss << msg;\
	common::logging::log( common::logging::createLog( common::logging::INFO_TAG, ss.str(), "", 0 ));\
}
#define LOG_DEBUG(msg){\
	std::stringstream ss;\
	ss << msg;\
	common::logging::log( common::logging::createLog( common::logging::DEBUG_TAG, ss.str(), __FILE__, __LINE__ ));\
}
#define LOG_ASSERT(msg){\
	std::stringstream ss;\
	ss << msg;\
	common::logging::log( common::logging::createLog( common::logging::ASSERT_TAG, ss.str(), __FILE__, __LINE__ ));\
}

}
}
