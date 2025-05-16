#include "UnitTests.h"

#include <ArdaCore/Array.h>

TESTGROUP(Array)
{
	UNITTEST(Array)
	{
		Array<int, 5> dummy({ 0, 1, 2, 3, 4 });
		CHECK_EQUAL(dummy[3], 3);

		dummy.FillArray(1);
		for (int val : dummy)
		{
			CHECK_EQUAL(val, 1);
		}
	}
}