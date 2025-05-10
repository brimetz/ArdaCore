#include "UnitTests.h"
#include <ArdaCore/Core.h>
#include <ArdaCore/StringView.h>
#include <string.h>

TESTGROUP(StringView)
{
	UNITTEST(Constructor)
	{
		StringView dummy;
		CHECK_EQUAL(dummy.Size(), 0);
		CHECK_EQUAL(dummy.Data(), nullptr);
		CHECK_EQUAL(dummy.IsEmpty(), true);

		const char* ptr = "Hola mi amigo !";
		StringView dummy2(ptr, 15);
		CHECK_EQUAL(dummy2.Size(), 15);
		CHECK_EQUAL(dummy2.Data(), ptr);
		CHECK_EQUAL(dummy2.IsEmpty(), false);

		StringView dummy3 = dummy2;
		CHECK_EQUAL(dummy3.Size(), 15);
		CHECK_EQUAL(dummy3.Data(), ptr);
		CHECK_EQUAL(dummy3.IsEmpty(), false);
	}

	UNITTEST(DeletePreAndSuffix)
	{
		char const* ptr = "Hola mi amigo !";
		StringView dummy(ptr, 15);

		dummy.DeletePrefix(4);
		CHECK_EQUAL(dummy.Size(), 11);
		CHECK_EQUAL(strncmp(dummy.Data(), " mi amigo !", dummy.Size()), 0);

		dummy.DeleteSuffix(2);
		CHECK_EQUAL(dummy.Size(), 9);
		CHECK_EQUAL(strncmp(dummy.Data(), " mi amigo", dummy.Size()), 0);
	}

	UNITTEST(StartsEndWith)
	{
		char const* ptr = "Hola mi amigo !";
		StringView dummy(ptr, 15);

		CHECK_EQUAL(dummy.StartsWith('H'), true);
		CHECK_EQUAL(dummy.StartsWith(StringView("Hola", 4)), true);

		CHECK_EQUAL(dummy.EndsWith('!'), true);
		CHECK_EQUAL(dummy.EndsWith(StringView("go !", 4)), true);
	}

	UNITTEST(ContainsAndFind)
	{
		char const* ptr = "Hola mi amigo !";
		StringView dummy(ptr, 15);

		CHECK_EQUAL(dummy.Contains('a'), true);
		CHECK_EQUAL(dummy.Contains(StringView("a mi", 4)), true);

		CHECK_EQUAL(dummy.Find('?'), -1);
		CHECK_EQUAL(dummy.Find('i'), 6);
		CHECK_EQUAL(dummy.Find(StringView("a mi", 4)), 3);
	}

	UNITTEST(SubString)
	{
		char const* ptr = "Hola mi amigo !";
		StringView dummy(ptr, 15);
		StringView subString = dummy.GetSubString(3, 4);
		CHECK_EQUAL(StringView("a mi", 4), subString);
	}
}