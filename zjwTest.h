#ifndef ZJWTEST_H
#define ZJWTEST_H
#include <cassert>
#include <string>

#include <boost/core/ignore_unused.hpp>

namespace zjw
{
class zjwTest
{
public:
#ifdef TEST
    static void testPreCodition(bool b,std::string const& condition)
    {
        assert(b);
    }

    static void testBackcondition(bool b,std::string const& condition)
    {
        assert(b);
    }
#else
    static void testPreCodition(bool b,std::string const& condition)
    {

    }

    static void testBackcondition(bool b,std::string const& condition)
    {
        assert(b);
    }
s#endifss//TEST
};
}
#endif // ZJWTEST_H
