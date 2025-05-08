#include "UnitTests.h"

#include <ArdaCore/Array.h>
#include <ArdaCore/DynamicArray.h>

TESTGROUP(DynamicArray)
{
	// Comparison function to gain time
	bool IsEqual(const auto & first, const auto & second)
	{
		if (first.Size() != second.Size())
		{
			return false;
		}

		for (int i = 0; i < first.Size(); i++)
		{
			if (*(first.Begin() + i) != *(second.Begin() + i))
			{
				return false;
			}
		}
		return true;
	}

	UNITTEST(ConstructorAndCopy)
	{
		DynamicArray<int> dummy = {1, 2, 3, 4, 5};
		CHECK_EQUAL(dummy.Size(), 5);
		CHECK_GREATEREQUAL(dummy.Capacity(), 5);

		DynamicArray copy = dummy;
		CHECK_EQUAL(copy.Size(), 5);
		CHECK_GREATEREQUAL(copy.Capacity(), 5);

		copy = std::move(dummy);
		CHECK_EQUAL(dummy.IsEmpty(), true);
	}

	struct TestStruct
	{
		TestStruct() : dummyInt(0) {}
		TestStruct(int inValue) : dummyInt(inValue) {}
		TestStruct(const TestStruct& inOther) : dummyInt(inOther.dummyInt) {}
		TestStruct(TestStruct&& inOther) : dummyInt(std::move(inOther.dummyInt)) {}
		TestStruct& operator=(const TestStruct& inOther)
		{
			dummyInt = inOther.dummyInt;
			return *this;
		}
		bool operator==(int inValue) const 
		{ 
			return inValue == dummyInt; 
		}
		int dummyInt;
	};

	UNITTEST(PushAndEmplaceBack)
	{
		DynamicArray<TestStruct> dummy;
		dummy.PushBack(TestStruct{ 0 });
		dummy.PushBack(1);
		dummy.PushBack(TestStruct{ 2 });

		CHECK_EQUAL(dummy.Size(), 3);
		CHECK_GREATEREQUAL(dummy.Capacity(), 3);
		DynamicArray<int> expected = { 0, 1, 2 };
		CHECK_EQUAL(IsEqual(dummy, expected), true);
	}

	UNITTEST(Insert)
	{
		DynamicArray<int> dummy{0, 1, 2, 3};
		dummy.Insert(1, 99);
		DynamicArray<int> expected = { 0, 99, 1, 2, 3 };
		CHECK_EQUAL(IsEqual(dummy, expected), true);
		
		dummy.Insert(4, 100);
		expected = {0, 99, 1, 2, 100, 3};
		CHECK_EQUAL(IsEqual(dummy, expected), true);

		dummy.Insert(3, -100);
		expected = { 0, 99, 1, -100, 2, 100, 3 };
		CHECK_EQUAL(IsEqual(dummy, expected), true);
	}

	UNITTEST(Resize)
	{
		DynamicArray<int> dummy;

		dummy.Resize(5, 10);

		DynamicArray<int> expected = {10, 10, 10, 10, 10};
		CHECK_EQUAL(IsEqual(dummy, expected), true);

		dummy.Resize(1);
		expected = {10};
		CHECK_EQUAL(IsEqual(dummy, expected), true); 

		dummy.PushBack(3);
		dummy.Resize(1);
		expected = { 10 };
		CHECK_EQUAL(IsEqual(dummy, expected), true);
	}

	UNITTEST(Erase)
	{
		DynamicArray<int> dummy = {1, 2, 3, 4, 5, 6};
		dummy.Erase(1);
		DynamicArray<int> expected = {1, 3, 4, 5, 6};
		CHECK_EQUAL(IsEqual(dummy, expected), true);

		dummy.Erase(4);
		expected = { 1, 3, 4, 5 };
		CHECK_EQUAL(IsEqual(dummy, expected), true);

		dummy.Erase(0);
		expected = { 3, 4, 5 };
		CHECK_EQUAL(IsEqual(dummy, expected), true);
	}
}