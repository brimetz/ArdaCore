#include "UnitTests.h"

#include <ArdaCore/Array.h>

TESTGROUP(Array)
{
	UNITTEST(Array)
	{
		Array<int, 5> dummy = {0, 1, 2, 3, 4};
		CHECK_EQUAL(dummy[3], 3)

		dummy.FillArray(1);
		for (int val : dummy)
		{
			CHECK_EQUAL(val, 1)
		}
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