#include "UnitTests.h"
#include <ArdaCore/Core.h>

#include <ArdaCore/String.h>
#include <ArdaCore/StringView.h>

/*
@todo list
- String
- Small String Optimization
- Algorythm Idea: BFS DFS Dijkstra A*
- Utilities with GeometricMean
- Hashing/HashMap
*/

// Test for WIP Feature

TESTGROUP(StringLarge)
{
	UNITTEST(Constructors)
	{
		String dummy(30, 'b');
		CHECK_EQUAL(dummy.Size(), 30);
		CHECK_EQUAL(dummy.Capacity(), 30);
		CHECK_EQUAL(dummy, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

		const char* test = "AAAAABBBBBCCCCCDDDDD";
		String dummy2(test);
		CHECK_EQUAL(dummy2.Size(), 20);
		CHECK_EQUAL(dummy2.Capacity(), 20);
		CHECK_EQUAL(dummy2, test);

		StringView View("ZZZZZWWWWWXXXXXYYYYY", 20);
		String dummyFromView(View);
		CHECK_EQUAL(dummyFromView.Size(), 20);
		CHECK_EQUAL(dummyFromView.Capacity(), 20);
		CHECK_EQUAL(dummyFromView, View);

		String dummyFromInitList({ 'a', 'a', 'a', 'a', 'a',
			'b', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'c', 'c', 'd', 'd', 'd', 'd', 'd' });
		std::initializer_list<char> list = { 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'c', 'c', 'd', 'd', 'd', 'd', 'd' };
		CHECK_EQUAL(dummyFromInitList.Size(), 20);
		CHECK_EQUAL(dummyFromInitList.Capacity(), 20);
		CHECK_EQUAL(dummyFromInitList, list);
	}

	UNITTEST(Operators)
	{
		String dummy("Hello World, How Are");
		dummy += " You";
		CHECK_EQUAL(dummy.Size(), 24);
		CHECK_EQUAL(dummy.Capacity(), 24);
		CHECK_EQUAL(dummy, "Hello World, How Are You");

		const char* str = " You";
		String dummy2("Hello World, How Are");
		dummy2 += str;
		CHECK_EQUAL(dummy2.Size(), 24);
		CHECK_EQUAL(dummy2.Capacity(), 24);
		CHECK_EQUAL(dummy2, "Hello World, How Are You");

		String FirstPart("Hello World, How");
		String SecondPart(" Are You");
		FirstPart += SecondPart;
		CHECK_EQUAL(FirstPart.Size(), 24);
		CHECK_EQUAL(FirstPart.Capacity(), 24);
		CHECK_EQUAL(FirstPart, "Hello World, How Are You");

		String dummy3("Hello World, How Are");
		dummy3 += { ' ', 'Y', 'o', 'u' };
		CHECK_EQUAL(dummy3.Size(), 24);
		CHECK_EQUAL(dummy3.Capacity(), 24);
		CHECK_EQUAL(dummy3, "Hello World, How Are You");
		
		String dummy4;
		dummy4 = "Hello World, How Are You";
		CHECK_EQUAL(dummy4.Size(), 24);
		CHECK_EQUAL(dummy4.Capacity(), 24);
		CHECK_EQUAL(dummy4, "Hello World, How Are You");

		str = "Hello World, How Are You";
		String dummy5;
		dummy5 = str;
		CHECK_EQUAL(dummy5.Size(), 24);
		CHECK_EQUAL(dummy5.Capacity(), 24);
		CHECK_EQUAL(dummy5, "Hello World, How Are You");

		String FirstPart2;
		String SecondPart2("Hello World, How Are You");
		FirstPart2 = SecondPart2;
		CHECK_EQUAL(FirstPart2.Size(), 24);
		CHECK_EQUAL(FirstPart2.Capacity(), 24);
		CHECK_EQUAL(FirstPart2, "Hello World, How Are You");

		String dummy6;
		dummy6 += { 'H', 'e', 'l', 'l', 'o',' ', 'W', 'o', 'r', 'l', 'd', ',', ' ','H','o','w',' ', 'A', 'r', 'e', ' ', 'Y', 'o', 'u' };
		CHECK_EQUAL(dummy6.Size(), 24);
		CHECK_EQUAL(dummy6.Capacity(), 24);
		CHECK_EQUAL(dummy6, "Hello World, How Are You");
	}

	UNITTEST(Insert)
	{
		String dummy("Hello , How Are You");
		dummy.Insert(6, "World");
		CHECK_EQUAL(dummy.Size(), 24);
		CHECK_EQUAL(dummy.Capacity(), 24);
		CHECK_EQUAL(dummy, "Hello World, How Are You");

		const char* str = "World";
		String dummy2("Hello , How Are You");
		dummy2.Insert(6, str);
		CHECK_EQUAL(dummy2.Size(), 24);
		CHECK_EQUAL(dummy2.Capacity(), 24);
		CHECK_EQUAL(dummy2, "Hello World, How Are You");

		String FirstPart("Hello World, How");
		String SecondPart(" Are You");
		FirstPart.Insert(FirstPart.Size(), SecondPart);
		CHECK_EQUAL(FirstPart.Size(), 24);
		CHECK_EQUAL(FirstPart.Capacity(), 24);
		CHECK_EQUAL(FirstPart, "Hello World, How Are You");

		String dummy3("Hello , How Are You");
		dummy3.Insert(6, {'W', 'o', 'r', 'l', 'd'});
		CHECK_EQUAL(dummy3.Size(), 24);
		CHECK_EQUAL(dummy3.Capacity(), 24);
		CHECK_EQUAL(dummy3, "Hello World, How Are You");
	}

	UNITTEST(Append)
	{
		String dummy("Hello World, How Are");
		dummy.Append(" You");
		CHECK_EQUAL(dummy.Size(), 24);
		CHECK_EQUAL(dummy.Capacity(), 24);
		CHECK_EQUAL(dummy, "Hello World, How Are You");

		const char* str = " You";
		String dummy2("Hello World, How Are");
		dummy2.Append(str);
		CHECK_EQUAL(dummy2.Size(), 24);
		CHECK_EQUAL(dummy2.Capacity(), 24);
		CHECK_EQUAL(dummy2, "Hello World, How Are You");

		String FirstPart("Hello World, How");
		String SecondPart(" Are You");
		FirstPart.Append(SecondPart);
		CHECK_EQUAL(FirstPart.Size(), 24);
		CHECK_EQUAL(FirstPart.Capacity(), 24);
		CHECK_EQUAL(FirstPart, "Hello World, How Are You");

		String dummy3("Hello World, How Are");
		dummy3.Append({' ', 'Y', 'o', 'u'});
		CHECK_EQUAL(dummy3.Size(), 24);
		CHECK_EQUAL(dummy3.Capacity(), 24);
		CHECK_EQUAL(dummy3, "Hello World, How Are You");
	}

	UNITTEST(Replace)
	{
		String dummy("Hello World, How Are You");
		dummy.Replace(6, 5, 5, 'b');
		CHECK_EQUAL(dummy, "Hello bbbbb, How Are You");

		String dummy2("Hello World, How Are You");
		dummy2.Replace(6, 5, "Mundo");
		CHECK_EQUAL(dummy2, "Hello Mundo, How Are You");

		String dummy3("Hello World, How Are You");
		String other("Comment Vas-tu");
		dummy3.Replace(13, 11, other);
		CHECK_EQUAL(dummy3, "Hello World, Comment Vas-tu");

		String dummy4("Hello World, How Are You");
		StringView view("Aurevoir", 8);
		dummy4.Replace(0, 5, view);
		CHECK_EQUAL(dummy4, "Aurevoir World, How Are You");

		String dummy5("Hello World, How Are You");
		std::initializer_list<char> list({'1', '2', '3', '4'});
		dummy5.Replace(13, 3, list);
		CHECK_EQUAL(dummy5, "Hello World, 1234 Are You");
	}

	UNITTEST(StartEndsWith)
	{
		String dummy("Hello World, How Are You");
		String starts("Hel");
		String ends("You");
		StringView viewStarts("Hel", 3);
		StringView viewEnds("You", 3);
		CHECK_EQUAL(dummy.StartsWith('H'), true);
		CHECK_EQUAL(dummy.StartsWith("Hello"), true);
		CHECK_EQUAL(dummy.StartsWith(starts), true);
		CHECK_EQUAL(dummy.StartsWith(viewStarts), true);
		CHECK_EQUAL(dummy.EndsWith('u'), true);
		CHECK_EQUAL(dummy.EndsWith("You"), true);
		CHECK_EQUAL(dummy.EndsWith(ends), true);
		CHECK_EQUAL(dummy.EndsWith(viewEnds), true);
	}

	UNITTEST(ContainsAndFind)
	{
		String dummy("Hello World, How Are You");
		String other("Are");
		StringView viewStarts(" How", 3);
		CHECK_EQUAL(dummy.Contains('H'), true);
		CHECK_EQUAL(dummy.Contains("Hello"), true);
		CHECK_EQUAL(dummy.Contains(other), true);
		CHECK_EQUAL(dummy.Contains(viewStarts), true);
		CHECK_EQUAL(dummy.Contains("Helw"), false);

		CHECK_EQUAL(dummy.Find('H', 2), 13);
		CHECK_EQUAL(dummy.Find("Hello"), 0);
		CHECK_EQUAL(dummy.Find(other), 17);
		CHECK_EQUAL(dummy.Find(viewStarts), 12);
	}

	UNITTEST(SubStringAndCompare)
	{
		String dummy("Hello World, How Are You");
		String other("Hello World, How Are You I");
		char test[] = "Heola Wordd,";
		StringView viewStarts(test, 12);
		CHECK_EQUAL(dummy.Compare("Hello"), 1);
		CHECK_LESSTHAN(dummy.Compare(viewStarts), 0)
		CHECK_EQUAL(dummy.Compare(other), -1);

		CHECK_EQUAL(dummy.GetSubString(6, 5), "World");
		CHECK_EQUAL(dummy.GetSubString(10), "d, How Are You");
	}

	UNITTEST(PushPopBack)
	{
		String dummy("Hello World, How Are You");
		dummy.PopBack();
		CHECK_EQUAL(dummy, "Hello World, How Are Yo");
		dummy.PushBack('o');
		CHECK_EQUAL(dummy, "Hello World, How Are Yoo");
	}

	UNITTEST(EraseResize)
	{
		String dummy("Hello World, How Are You");
		dummy.Erase(6, 5);
		CHECK_EQUAL(dummy, "Hello , How Are You");

		dummy.Resize(12);
		CHECK_EQUAL(dummy, "Hello , How ");
		dummy.Resize(30, 'b');
		CHECK_EQUAL(dummy.Size(), 30);
		CHECK_EQUAL(dummy.Capacity(), 30);
		CHECK_EQUAL(dummy, "Hello , How bbbbbbbbbbbbbbbbbb");
	}

	UNITTEST(ClearReserveAndShrink)
	{
		String dummy;
		dummy.Reserve(30);
		dummy = ("Hello World, How Are You");
		CHECK_EQUAL(dummy.Size(), 24);
		CHECK_EQUAL(dummy.Capacity(), 30);
		dummy.ShrinkToFit();
		CHECK_EQUAL(dummy.Size(), 24);
		CHECK_EQUAL(dummy.Capacity(), 24);
		dummy.Clear();
		CHECK_EQUAL(dummy.Size(), 0);
		CHECK_EQUAL(dummy.Capacity(), 24);
		CHECK_EQUAL(dummy, "");
	}
}

TESTGROUP(StringSmall)
{
	UNITTEST(Constructors)
	{

	}

	UNITTEST(Operators)
	{

	}
	UNITTEST(Insert)
	{

	}

	UNITTEST(Append)
	{

	}

	UNITTEST(Replace)
	{

	}

	UNITTEST(StartEndsWith)
	{

	}

	UNITTEST(ContainsAndFind)
	{

	}

	UNITTEST(SubStringAndCompare)
	{

	}

	UNITTEST(PushPopBack)
	{

	}

	UNITTEST(EraseResize)
	{

	}

	UNITTEST(ClearReserveAndShrink)
	{

	}
}