#include "UnitTests.h"

#include <ArdaCore/ArrayView.h>

TESTGROUP(ArrayView)
{
	UNITTEST(Constructor)
	{
		uint32 test[5]{ 0, 1, 2, 3, 4 };
		ArrayView dummy(test);
		CHECK_EQUAL(dummy.Size(), 5);
		for (int i{ 0 }; i < dummy.Size(); ++i)
		{
			CHECK_EQUAL(dummy[i], i)
		}

		uint32* dummyOnHeap = new uint32[5]{ 0, 1, 2, 3, 4 };
		ArrayView Copy{ dummyOnHeap, 5 };
		CHECK_EQUAL(Copy.Size(), 5);
		for (int i{ 0 }; i < Copy.Size(); ++i)
		{
			CHECK_EQUAL(Copy[i], i);
		}

		delete[] dummyOnHeap;
	}

	UNITTEST(Operator)
	{
		int test[] = { 0, 1, 2, 3, 4 };
		int test2[] = { 0, 0, 2, 3, 0 };

		ArrayView dummy(test);
		ArrayView dummyEqual(test);
		CHECK_EQUAL(dummy == dummyEqual, true);

		ArrayView dummyNotEqual(test2);
		CHECK_EQUAL(dummy == dummyNotEqual, false);

		ArrayView dummy4(dummyEqual);
		CHECK_EQUAL(dummy4 == dummyEqual, true);

		ArrayView dummy5{ArrayView(test)};
		CHECK_EQUAL(dummy5 == ArrayView(test), true);
	}

	UNITTEST(SubArray)
	{
		int test[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int test2[] = { 0, 1, 2, 3 };
		int test3[] = { 6, 7, 8, 9 };
		int test4[] = { 4, 5, 6 };

		ArrayView dummy(test);

		ArrayView Start(dummy.GetStartTo(4));
		CHECK_EQUAL(Start == ArrayView(test2), true);

		ArrayView End(dummy.GetEndFrom(4));
		CHECK_EQUAL(End == ArrayView(test3), true);
		ArrayView SubPart(dummy.GetSubArray(4, 3));
		CHECK_EQUAL(SubPart == ArrayView(test4), true);
	}
}