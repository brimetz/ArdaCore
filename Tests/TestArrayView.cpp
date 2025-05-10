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
		ArrayView dummy({ 0, 1, 2, 3, 4 });
		ArrayView dummyEqual({ 0, 1, 2, 3, 4 });
		CHECK_EQUAL(dummy == dummyEqual, true);

		ArrayView dummyNotEqual({ 0, 0, 2, 3, 0 });
		CHECK_EQUAL(dummy == dummyNotEqual, false);

		ArrayView dummy4(dummyEqual);
		CHECK_EQUAL(dummy4 == dummyEqual, true);

		ArrayView dummy5(ArrayView({ 0, 1, 2, 3, 4 }));
		CHECK_EQUAL(dummy5 == ArrayView({ 0, 1, 2, 3, 4 }), true);
	}

	UNITTEST(SubArray)
	{
		ArrayView dummy({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

		ArrayView Start(dummy.GetStartTo(4));
		CHECK_EQUAL(Start == ArrayView({ 0, 1, 2, 3 }), true);

		ArrayView End(dummy.GetEndFrom(4));
		CHECK_EQUAL(End == ArrayView({ 6, 7, 8, 9 }), true);
		ArrayView SubPart(dummy.GetSubArray(4, 3));
		CHECK_EQUAL(SubPart == ArrayView({ 4, 5, 6 }), true);
	}
}