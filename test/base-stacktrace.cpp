/* Icinga 2 | (c) 2020 Icinga GmbH | GPLv2+ */

#include "base/stacktrace.hpp"
#include <BoostTestTargetConfig.h>

using namespace icinga;

BOOST_AUTO_TEST_SUITE(base_stacktrace)

[[gnu::noinline]]
boost::stacktrace::stacktrace stack_test_func_b()
{
	return boost::stacktrace::stacktrace();
}

[[gnu::noinline]]
boost::stacktrace::stacktrace stack_test_func_a()
{
	return stack_test_func_b();
}

BOOST_AUTO_TEST_CASE(stacktrace)
{
	boost::stacktrace::stacktrace stack = stack_test_func_a();
	std::ostringstream obuf;
	obuf << StackTraceFormatter(stack);
	std::string result = obuf.str();
	BOOST_CHECK_MESSAGE(!result.empty(), "stack trace must not be empty");
	size_t pos_a = result.find("stack_test_func_a");
	size_t pos_b = result.find("stack_test_func_b");
	BOOST_CHECK_MESSAGE(pos_a != std::string::npos, "'stack_test_func_a' not found");
	BOOST_CHECK_MESSAGE(pos_b != std::string::npos, "'stack_test_func_b' not found");
	BOOST_CHECK_MESSAGE(pos_a > pos_b, "'stack_test_func_a' must appear after 'stack_test_func_b'");
}

BOOST_AUTO_TEST_SUITE_END()
