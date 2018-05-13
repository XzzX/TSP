#pragma once

#include "log.h"
#include "macros.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

namespace common {
namespace debug {

#define ASSERT_1(X)         { do { if( !((X)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), #X, "" ) ); exit(-1);} } while (0); }
#define ASSERT_2(X,MSG)     { do { if( !(!(X)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), #X, "" ) << "\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT(...)               MACRO_OVERLOAD( ASSERT_, __VA_ARGS__ )

#define ASSERT_NULLPTR_1(X)         { do { if( !((X) == nullptr) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), #X, "nullptr" ) ); exit(-1); } } while (0); }
#define ASSERT_NULLPTR_2(X,MSG)     { do { if( !((X) == nullptr) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), #X, "nullptr" ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_NULLPTR(...)               MACRO_OVERLOAD( ASSERT_EQUAL_, __VA_ARGS__ )

#define ASSERT_NOT_NULLPTR_1(X)         { do { if( !((X) != nullptr) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), #X, "!nullptr" ) ); exit(-1); } } while (0); }
#define ASSERT_NOT_NULLPTR_2(X,MSG)     { do { if( !((X) != nullptr) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), #X, "!nullptr" ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_NOT_NULLPTR(...)               MACRO_OVERLOAD( ASSERT_NOT_NULLPTR_, __VA_ARGS__ )

#define ASSERT_EQUAL_2(X,Y)         { do { if( !((X) == (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " == " ) ); exit(-1); } } while (0); }
#define ASSERT_EQUAL_3(X,Y,MSG)     { do { if( !((X) == (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " == " ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_EQUAL(...)               MACRO_OVERLOAD( ASSERT_EQUAL_, __VA_ARGS__ )

#define ASSERT_NOT_EQUAL_2(X,Y)         { do { if( !((X) != (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " != " ) ); exit(-1); } } while (0); }
#define ASSERT_NOT_EQUAL_3(X,Y,MSG)     { do { if( !((X) != (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " != " ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_NOT_EQUAL(...)               MACRO_OVERLOAD( ASSERT_NOT_EQUAL_, __VA_ARGS__ )

#define ASSERT_GREATER_2(X,Y)         { do { if( !((X) > (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " > " ) ); exit(-1); } } while (0); }
#define ASSERT_GREATER_3(X,Y,MSG)     { do { if( !((X) > (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " > " ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_GREATER(...)               MACRO_OVERLOAD( ASSERT_GREATER_, __VA_ARGS__ )

#define ASSERT_LESS_2(X,Y)         { do { if( !((X) < (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " < " ) ); exit(-1); } } while (0); }
#define ASSERT_LESS_3(X,Y,MSG)     { do { if( !((X) < (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " < " ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_LESS(...)               MACRO_OVERLOAD( ASSERT_LESS_, __VA_ARGS__ )

#define ASSERT_GREATEREQUAL_2(X,Y)         { do { if( !((X) >= (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " >= " ) ); exit(-1); } } while (0); }
#define ASSERT_GREATEREQUAL_3(X,Y,MSG)     { do { if( !((X) >= (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " >= " ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_GREATEREQUAL(...)               MACRO_OVERLOAD( ASSERT_GREATEREQUAL_, __VA_ARGS__ )

#define ASSERT_LESSEQUAL_2(X,Y)         { do { if( !((X) <= (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " <= " ) ); exit(-1); } } while (0); }
#define ASSERT_LESSEQUAL_3(X,Y,MSG)     { do { if( !((X) <= (Y)) ) { LOG_FATAL( common::debug::generateAssertionMessage( (X), (Y), #X, #Y, " <= " ) << "\n\n" << (MSG) ); exit(-1); } } while (0); }
#define ASSERT_LESSEQUAL(...)               MACRO_OVERLOAD( ASSERT_LESSEQUAL_, __VA_ARGS__ )

template< typename T >
std::string generateAssertionMessage( const T& lhs, const std::string& lhsExpression, const std::string& opString )
{
   std::stringstream ss;
   int length = static_cast<int>( lhsExpression.length() );
   ss  << "Assertion failed!\n"
       << "Expression: " << opString << "( " << lhsExpression << " )\n"
       << "Value:     " << std::setw(length) << std::setfill(' ') << lhsExpression << " = " << lhs;
  return ss.str();
}

template< typename T, typename U >
std::string generateAssertionMessage( const T& lhs, const U& rhs, const std::string& lhsExpression, const std::string& rhsExpression,
                        const std::string& opString )
{
   std::stringstream ss;
   int length = static_cast<int>( std::max( lhsExpression.length(), rhsExpression.length() ) );
   ss  << "Assertion failed!\n"
       << "Expression: " << lhsExpression << opString << rhsExpression << '\n'
       << "Values:     " << std::setw(length) << std::setfill(' ') << lhsExpression << " = " << lhs << '\n'
       << "            " << std::setw(length) << std::setfill(' ') << rhsExpression << " = " << rhs;
  return ss.str();
}

} //debug
} //common
