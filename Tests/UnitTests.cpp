#include "UnitTests.h"

TestUnit& TestUnit::GetInstance()
{
	static TestUnit Intance;
	return Intance;
}

TestUnit::~TestUnit()
{
	if (groups)
	{
		free(groups);
	}
}

int TestUnit::RunTestGroups()
{
	bool fail = false;
	for (uint32 i{ 0 }; i < groupsSize; ++i)
	{
		printf("[%s]\n", groups[i]->name);
		groups[i]->RunTests();
		if (groups[i]->testsFailCount)
		{
			fail = true;
			printf("[" RED "fail" DEFAULT "] (%d/%d)\n\n", groups[i]->testsSize - 
				groups[i]->testsFailCount, groups[i]->testsSize);
		}
		else
		{
			printf("[" GREEN "pass" DEFAULT "]   (%d/%d)\n\n",
				groups[i]->testsSize, groups[i]->testsSize);
		}
	}

	printf("summary:\n");
	for (uint32 i{ 0 }; i < groupsSize; ++i)
	{
		if (groups[i]->testsFailCount)
		{
			printf("[%s] [" RED "fail" DEFAULT "] (%d/%d)\n",
				groups[i]->name, groups[i]->testsSize - groups[i]->testsFailCount,
				groups[i]->testsSize);
		}
		else
		{
			printf("[%s] [" GREEN "pass" DEFAULT "] (%d/%d)\n", groups[i]->name,
				groups[i]->testsSize, groups[i]->testsSize);
		}
	}
	return fail;
}

void TestUnit::AddTestGroup(TestGroup_Base* newGroup)
{
	// Increase array capacity if we reach it
	if (!groupsCap)
	{
		groups = reinterpret_cast<TestGroup_Base**>(
			malloc(sizeof(TestGroup_Base*)));
		groupsCap = 1;
	}
	else if (groupsSize == groupsCap)
	{
		groupsCap *= 2;
		groups = reinterpret_cast<TestGroup_Base**>(realloc(groups, 
			sizeof(TestGroup_Base*) * groupsCap));
	}

	// Find the first slot available in the groups array
	uint32 pos = groupsSize;
	while (pos > 0)
	{
		if (strcmp(newGroup->name, groups[pos - 1]->name) >= 0)
		{
			break;
		}

		--pos;
	}

	for (uint32 i{ groupsSize }; i > pos; --i)
	{
		groups[i] = groups[i - 1];
	}

	groups[pos] = newGroup;
	++groupsSize;
}

TestGroup_Base::TestGroup_Base(char const* name)
	: name {name}
{
	TestUnit::GetInstance().AddTestGroup(this);
}

TestGroup_Base::~TestGroup_Base()
{
	if (tests)
	{
		free(tests);
	}
}

void TestGroup_Base::RunTests()
{
	for (uint32 i{ 0 }; i < testsSize; ++i)
	{
		printf("|-[%s]\n", tests[i]->name);
		tests[i]->Run();
		if (tests[i]->checksFailCount)
		{
			printf("|-[" RED "fail" DEFAULT "] (%d/%d)\n",
				tests[i]->checksCount - tests[i]->checksFailCount, tests[i]->checksCount);
			++testsFailCount;
		}
		else
		{
			printf("|-[" GREEN "pass" DEFAULT "] (%d/%d)\n", tests[i]->checksCount,
				tests[i]->checksCount);
		}
	}
}

void TestGroup_Base::AddTest(TestBase* newTest)
{
	// Increase array capacity if we reach it
	if (!testsCap)
	{
		tests = reinterpret_cast<TestBase**>(malloc(sizeof(TestBase*)));
		testsCap = 1;
	}
	else if (testsSize == testsCap)
	{
		testsCap *= 2;
		tests = reinterpret_cast<TestBase**>(realloc(tests, 
			sizeof(TestBase*) * testsCap));
	}

	// add the new test in the array and update its current size
	tests[testsSize] = newTest;
	++testsSize;
}