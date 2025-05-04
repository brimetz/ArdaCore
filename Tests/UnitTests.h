#pragma once

#include <stdint.h>

#include <stdio.h>
#include <cstdlib>
#include <cstring>

#define TESTGROUP(Name)									\
	namespace NAMESPACE_TestGroup_##Name				\
	{													\
		struct TestGroup_##Name : public TestGroup_Base \
		{                                               \
			TestGroup_##Name()                          \
			: TestGroup_Base(#Name)                     \
			{}                                          \
		};                                              \
		TestGroup_##Name group_instance;                \
	}                                                   \
	namespace NAMESPACE_TestGroup_##Name							

#define UNITTEST(Name)                                     \
	struct Test##Name : public TestBase                    \
	{                                                      \
		Test##Name(TestGroup_Base* group)                  \
		: TestBase(#Name, group)                           \
		{}                                                 \
		void Run() override;                               \
	};                                                     \
	Test##Name Test##Name##_GetInstance(&group_instance);  \
	void        Test##Name::Run()

#define CHECK_EQUAL(a, b)										   \
	if ((a) != (b))                                                \
	{                                                              \
		++checksFailCount;                                         \
		++checksCount;                                             \
		print_check_error(a, b, #a, #b, "==", __LINE__, __FILE__); \
	}                                                              \
	else                                                           \
	{                                                              \
		++checksCount;                                             \
	}

#define CHECK_NOTEQUAL(a, b)									   \
	if ((a) == (b))                                                \
	{                                                              \
		++checksFailCount;                                         \
		++checksCount;                                             \
		print_check_error(a, b, #a, #b, "!=", __LINE__, __FILE__); \
	}                                                              \
	else                                                           \
	{                                                              \
		++checksCount;                                             \
	}

#define CHECK_GREATERTHAN(a, b)									   \
	if ((a) <= (b))                                                \
	{                                                              \
		++checksFailCount;                                         \
		++checksCount;                                             \
		print_check_error(a, b, #a, #b, ">", __LINE__, __FILE__);  \
	}                                                              \
	else                                                           \
	{                                                              \
		++checksCount;                                             \
	}

#define CHECK_GREATEREQUAL(a, b)								   \
	if ((a) < (b))                                                 \
	{                                                              \
		++checksFailCount;                                         \
		++checksCount;                                             \
		print_check_error(a, b, #a, #b, ">=", __LINE__, __FILE__); \
	}                                                              \
	else                                                           \
	{                                                              \
		++checksCount;                                             \
	}

#define CHECK_LESSTHAN(a, b)										\
	if ((a) >= (b))													\
	{																\
		++checksFailCount;											\
		++checksCount;												\
		print_check_error(a, b, #a, #b, "<", __LINE__, __FILE__);	\
	}																\
	else															\
	{																\
		++checksCount;												\
	}

#define CHECK_LESSEQUAL(a, b)										\
	if ((a) > (b))													\
	{																\
		++checksFailCount;											\
		++checksCount;												\
		print_check_error(a, b, #a, #b, "<=", __LINE__, __FILE__);	\
	}																\
	else															\
	{																\
		++checksCount;												\
	}

struct TestBase;
struct TestGroup_Base;

struct TestUnit
{
	static TestUnit& GetInstance();

	~TestUnit();

	// Run each group of tests
	int RunTestGroups();

	void AddTestGroup(TestGroup_Base* newGroup);

	TestGroup_Base** groups = nullptr;
	uint32_t groupsSize = 0;
	uint32_t groupsCap = 0;
};

struct TestGroup_Base
{
	TestGroup_Base(char const* name);
	virtual ~TestGroup_Base();

	// Function used to Run all the test in the group
	void RunTests();

	// Add a test to this group. all the test in the same group will be run together
	void AddTest(TestBase* newTest);

	char const* name;
	TestBase** tests{ nullptr };
	uint32_t testsSize = 0;
	uint32_t testsCap = 0;

	uint32_t testsFailCount = 0;
};

struct TestBase
{
	TestBase(char const* name, TestGroup_Base* testGroup) :
		name {name}
	{
		testGroup->AddTest(this);
	}

	virtual void Run() = 0;

	char const* name;
	uint32_t checksCount = 0;
	uint32_t checksFailCount = 0;
};


// Resolved at compilation for optimisation. Specialized this template to return true or false at compilation
template <typename, typename>
constexpr bool is_same_v = false;

template <typename T>
constexpr bool is_same_v<T, T> = true;

template <typename>
constexpr bool is_pointer_v = false;

template <typename T>
constexpr bool is_pointer_v<T*> = true;

template <typename T>
bool PrintValue(char* buf, char const* valStr, T const& val)
{
	if constexpr (is_same_v<T, int8_t> || is_same_v<T, int16_t> || is_same_v<T, int32_t>)
	{
		snprintf(buf, 64, "%i", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, int64_t>)
	{
		snprintf(buf, 64, "%ji", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, uint8_t> || is_same_v<T, uint16_t> ||
		is_same_v<T, uint32_t>)
	{
		snprintf(buf, 64, "%u", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, uint64_t>)
	{
		snprintf(buf, 64, "%ju", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, float> || is_same_v<T, double>)
	{
		snprintf(buf, 64, "%f", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, char>)
	{
		snprintf(buf, 64, "'%c'", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, char const*> || is_same_v<T, char*>)
	{
		snprintf(buf, 64, "\"%s\"", val);
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_same_v<T, bool>)
	{
		strcpy(buf, val ? "true" : "false");
		return strcmp(buf, valStr) != 0;
	}
	else if constexpr (is_pointer_v<T>)
	{
		bool simple_ptr = print_value(buf, valStr, *val);
		if (!simple_ptr)
		{
			snprintf(buf, 64, "%p", val);
		}

		return true;
	}
	else
	{
		// Non-trivial type, no simple way to parse it
		return false;
	}
}

// Define Console color
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define DEFAULT "\x1b[0m"

template <typename T1, typename T2>
void print_check_error(T1 const& a, T2 const& b, char const* aStr, char const* bStr,
	char const* op, int line, char const* file)
{
	char buf1[64], buf2[64];
	bool needPrintA = PrintValue(buf1, aStr, a);
	bool needPrintB = PrintValue(buf2, bStr, b);
	printf("||-[" RED "fail" DEFAULT "]: ");
	if (needPrintA)
	{
		printf("%s(%s) ", aStr, buf1);
	}
	else
	{
		printf("%s ", aStr);
	}

	printf("%s ", op);
	if (needPrintB)
	{
		printf("%s(%s) ", bStr, buf2);
	}
	else
	{
		printf("%s ", bStr);
	}
	printf("(%s:%d)\n", file, line);
}