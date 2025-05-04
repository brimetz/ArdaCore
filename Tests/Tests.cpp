#include "UnitTests.h"

#include <ArdaCore/Array.h>

TESTGROUP(Array)
{
	UNITTEST(Constructor)
	{
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(0, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
	}

	UNITTEST(Addition)
	{
		CHECK_EQUAL(0, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(0, 1)
		CHECK_EQUAL(1, 1)
	}
}

TESTGROUP(Vector)
{
	UNITTEST(Constructor)
	{
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
	}

	UNITTEST(Addition)
	{
		CHECK_EQUAL(0, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(1, 1)
		CHECK_EQUAL(0, 1)
		CHECK_EQUAL(1, 1)
	}
}

/*template <typename, typename>
constexpr bool is_same_v = false;

template <typename T>
constexpr bool is_same_v<T, T> = true;

is_same_v<float, float>

is_same_v<float, double>

is_*/