#include <ArdaCore/String.h>

#include <ArdaCore/Assert.h>

// for memset and strncmp
#include <string.h>
// for new and free
#include <new>


// Info From a friend
// The user-defined ctor is needed because clang and gcc (< 13) misunderstand the
// union not being trivially constructible.
// See https://github.com/llvm/llvm-project/pull/82407 for the clang fix.
String::String() :
	m_size {0}
{}

String::String(uint32 inCount, char c) :
	m_size{ inCount }
{
	Large.m_capacity = inCount;
	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	Large.m_data = new char[inCount+1];
	// use memset to copy c in our data @todo make my own
	memset(Large.m_data, c, inCount);
	Large.m_data[inCount] = '\0';
}

String::String(const char* inStr, uint32 inCount)
{ 
	if (inCount == UINT32_MAX)
	{
		// @todo create my own strlen
		m_size = strlen(inStr);
	}
	else
	{
		m_size = inCount;
	}

	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	Large.m_data = new char[m_size+1];
	Large.m_capacity = m_size;
	// use memset to copy c in our data @todo make my own memcpy
	memcpy(Large.m_data, inStr, m_size);
	Large.m_data[m_size] = '\0';
}

String::String(StringView inStr, uint32 inPos, uint32 inCount)
{
	if (inCount == UINT32_MAX)
	{
		m_size = inStr.Size() - inPos;
	}
	else
	{
		m_size = inCount;
	}

	Large.m_capacity = m_size;
	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	Large.m_data = new char[m_size+1];
	// @todo make my own memcpy
	memcpy(Large.m_data, inStr.Data() + inPos, m_size);
	Large.m_data[m_size] = '\0';
}

String::String(const String& inStr, uint32 inPos, uint32 inCount)
{
	if (inCount == UINT32_MAX)
	{
		m_size = inStr.m_size - inPos;
	}
	else
	{
		m_size = inCount;
	}

	Large.m_capacity = m_size;
	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	Large.m_data = new char[m_size+1];
	// @todo make my own memcpy
	memcpy(Large.m_data, inStr.Data() + inPos, m_size);
	Large.m_data[m_size] = '\0';
}

String::String(String&& inStr, uint32 inPos, uint32 inCount)
{
	if (inCount == UINT32_MAX)
	{
		m_size = inStr.m_size - inPos;
	}
	else
	{
		m_size = inCount;
	}

	Large.m_capacity = m_size;
	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	Large.m_data = new char[m_size+1];
	// @todo make my own memmove
	memmove(Large.m_data, inStr.Data() + inPos, m_size);
	Large.m_data[m_size] = '\0';
}

String::String(const std::initializer_list<char> inList) :
	m_size {static_cast<uint32>(inList.size())}
{
	Large.m_capacity = m_size;
	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	Large.m_data = new char[m_size+1];
	// @todo make my own memmove
	memcpy(Large.m_data, inList.begin(), m_size);
	Large.m_data[m_size] = '\0';
}

String::~String()
{
	free(Large.m_data);
}

String& String::operator=(const char* inStr)
{
	uint32 inStrSize = strlen(inStr);

	if (inStrSize >= Large.m_capacity)
	{
		free(Large.m_data);
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inStrSize + 1];
		Large.m_data = newData;
		Large.m_capacity = inStrSize;
	}
	memcpy(Large.m_data, inStr, inStrSize);
	Large.m_data[inStrSize] = '\0';
	m_size = inStrSize;
	return *this;
}

String& String::operator=(StringView inStr)
{
	uint32 inStrSize = inStr.Size();

	if (inStrSize >= Large.m_capacity)
	{
		free(Large.m_data);
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inStrSize + 1];
		Large.m_data = newData;
		Large.m_capacity = inStrSize;
	}
	memcpy(Large.m_data, inStr.Data(), inStrSize);
	Large.m_data[inStrSize] = '\0';
	m_size = inStrSize;
	return *this;
}

String& String::operator=(const String& inStr)
{
	uint32 inStrSize = inStr.Size();

	if (inStrSize >= Large.m_capacity)
	{
		free(Large.m_data);
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inStrSize + 1];
		Large.m_data = newData;
		Large.m_capacity = inStrSize;
	}
	memcpy(Large.m_data, inStr.Data(), inStrSize);
	Large.m_data[inStrSize] = '\0';
	m_size = inStrSize;
	return *this;
}

String& String::operator=(String&& inStr)
{
	uint32 inStrSize = inStr.Size();

	if (inStrSize >= Large.m_capacity)
	{
		free(Large.m_data);
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inStrSize + 1];
		Large.m_data = newData;
		Large.m_capacity = inStrSize;
	}
	memmove(Large.m_data, inStr.Data(), inStrSize);
	Large.m_data[inStrSize] = '\0';
	m_size = inStrSize;
	return *this;
}

String& String::operator=(std::initializer_list<char> inList)
{
	uint32 inListSize = inList.size();

	if (inListSize >= Large.m_capacity)
	{
		free (Large.m_data);
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inListSize + 1];
		Large.m_data = newData;
		Large.m_capacity = inListSize;
	}
	memcpy(Large.m_data, inList.begin(), inListSize);
	Large.m_data[inListSize] = '\0';
	m_size = inListSize;
	return *this;
}

String& String::operator+=(const char* inStr)
{
	Append(inStr);
	return *this;
}

String& String::operator+=(StringView inStr)
{
	Append(inStr);
	return *this;
}

String& String::operator+=(const String& inStr)
{
	Append(inStr);
	return *this;
}

String& String::operator+=(std::initializer_list<char> inList)
{
	Append(inList);
	return *this;
}

bool String::operator==(const String& inStr) const
{
	if (m_size != inStr.Size())
		return false;
	return strncmp(Large.m_data, inStr.Data(), m_size) == 0;
}

bool String::operator==(StringView inStr) const
{
	if (m_size != inStr.Size())
		return false;
	return strncmp(Large.m_data, inStr.Data(), m_size) == 0;
}

bool String::operator==(const char* inStr) const
{
	float test = strlen(inStr);
	if (m_size != test)
		return false;
	return strncmp(Large.m_data, inStr, m_size) == 0;
}

char& String::operator[](uint32 inPos)&
{
	return Large.m_data[inPos];
}

char const& String::operator[](uint32 inPos) const&
{
	return Large.m_data[inPos];
}

void String::Clear()
{
	Large.m_data[0] = '\0';
	m_size = 0;
}

void String::Reserve(uint32 inCapacity)
{
	if (Large.m_capacity >= inCapacity)
	{
		return;
	}

	// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
	char* newData = new char[inCapacity];

	if (Large.m_capacity != 0)
	{
		memcpy(newData, Large.m_data, m_size + 1);
		free(Large.m_data);
	}

	Large.m_data = newData;
	Large.m_capacity = inCapacity;
}

void String::ShrinkToFit()
{
	if (m_size != Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[m_size+1];
		memcpy(newData, Large.m_data, m_size + 1);
		free(Large.m_data);

		Large.m_data = newData;
		Large.m_capacity = m_size;
	}
}

void String::Resize(uint32 inSize, char c)
{
	if (inSize < m_size)
	{
		Large.m_data[inSize] = '\0';
		m_size = inSize;
		return;
	}

	if (inSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inSize+1];

		memcpy(newData, Large.m_data, m_size);

		free(Large.m_data);
		Large.m_data = newData;
		memset(Large.m_data + m_size, c, inSize - m_size);

		Large.m_capacity = inSize;
	}
	else
	{
		memset(Large.m_data + m_size, c, inSize - m_size);
	}

	Large.m_data[inSize] = '\0';
	m_size = inSize;
}

void String::Insert(uint32 idx, uint32 inCount, char c)
{
	if (idx == m_size)
	{
		Append(inCount, c);
		return;
	}

	uint32 FutureSize = inCount + m_size;
	if (FutureSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[FutureSize+1];

		// put the old data inside the new array
		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inCount, Large.m_data + idx, m_size - idx + 1);

		// Remove and free the old array
		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = FutureSize;
	}
	else
	{
		// Create the hole in memory for inList data 
		memmove(Large.m_data + idx + inCount, Large.m_data + idx,
			m_size - idx + 1);
	}
	// Put the inList data inside the new array at the right position
	memset(Large.m_data + idx, c, inCount);
	m_size = FutureSize;
}

void String::Insert(uint32 idx, const char* inStr, uint32 inCount)
{
	if (idx == m_size)
	{
		Append(inStr);
		return;
	}

	uint32 inListSize = strlen(inStr);
	uint32 FutureSize = inListSize + m_size;
	if (FutureSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[FutureSize+1];

		// put the old data inside the new array
		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);

		// Remove and free the old array
		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = FutureSize;
	}
	else
	{
		// Create the hole in memory for inList data 
		memmove(Large.m_data + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);
	}
	// Put the inList data inside the new array at the right position
	memcpy(Large.m_data + idx, inStr, inListSize);
	m_size = FutureSize;
}

void String::Insert(uint32 idx, const String& inStr, uint32 inPos, uint32 inCount)
{
	if (idx == m_size)
	{
		Append(inStr);
		return;
	}

	uint32 inListSize = inStr.Size();
	uint32 FutureSize = inListSize + m_size;
	if (FutureSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[FutureSize+1];

		// put the old data inside the new array
		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);

		// Remove and free the old array
		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = FutureSize;
	}
	else
	{
		// Create the hole in memory for inList data 
		memmove(Large.m_data + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);
	}
	// Put the inList data inside the new array at the right position
	memcpy(Large.m_data + idx, inStr.Data(), inListSize);
	m_size = FutureSize;
}

void String::Insert(uint32 idx, const StringView& inStr, uint32 inPos, uint32 inCount)
{
	if (idx == m_size)
	{
		Append(inStr);
		return;
	}

	uint32 inListSize = inStr.Size();
	uint32 FutureSize = inListSize + m_size;
	if (FutureSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[FutureSize+1];

		// put the old data inside the new array
		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);

		// Remove and free the old array
		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = FutureSize;
	}
	else
	{
		// Create the hole in memory for inList data 
		memmove(Large.m_data + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);
	}
	// Put the inList data inside the new array at the right position
	memcpy(Large.m_data + idx, inStr.Data(), inListSize);
	m_size = FutureSize;
}

void String::Insert(uint32 idx, const std::initializer_list<char>& inList)
{
	if (idx == m_size)
	{
		Append(inList);
		return;
	}

	uint32 inListSize = inList.size();
	uint32 FutureSize = inListSize + m_size;
	if (FutureSize > Large.m_capacity)
	{
		// @todo replace that new by an alloc because new initialized data but we don't want that
		char* newData = new char[FutureSize+1];

		// put the old data inside the new array
		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);

		// Remove and free the old array
		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = FutureSize;
	}
	else
	{
		// Create the hole in memory for inList data 
		memmove(Large.m_data + idx + inListSize, Large.m_data + idx,
			m_size - idx + 1);
	}
	// Put the inList data inside the new array at the right position
	memcpy(Large.m_data + idx, inList.begin(), inListSize);
	m_size = FutureSize;
}

void String::Append(uint32 inCount, char c)
{
	uint32 newSize = m_size + inCount;
	if (newSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newSize];

		memcpy(newData, Large.m_data, m_size);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newSize;
	}

	memset(Large.m_data + m_size, c, inCount);
	Large.m_data[newSize] = '\0';
	m_size = newSize;
}

void String::Append(const char* inStr, uint32_t inCount)
{
	if (inCount == UINT32_MAX)
	{
		inCount = strlen(inStr);
	}

	uint32_t newTotalSize = m_size + inCount;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, m_size);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	memcpy(Large.m_data + m_size, inStr, inCount);
	Large.m_data[newTotalSize] = '\0';
	m_size = newTotalSize;
}

void String::Append(const String& inStr, uint32_t inPos, uint32_t inCount)
{
	if (inCount == UINT32_MAX)
	{
		inCount = inStr.Size() - inPos;
	}

	uint32_t newTotalSize = m_size + inCount;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, m_size);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	memcpy(Large.m_data + m_size, inStr.Data() + inPos, inCount);
	Large.m_data[newTotalSize] = '\0';
	m_size = newTotalSize;
}

void String::Append(const StringView inStr, uint32_t inPos, uint32_t inCount)
{
	if (inCount == UINT32_MAX)
	{
		inCount = inStr.Size() - inPos;
	}

	uint32_t newTotalSize = m_size + inCount;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, m_size);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	memcpy(Large.m_data + m_size, inStr.Data() + inPos, inCount);
	Large.m_data[newTotalSize] = '\0';
	m_size = newTotalSize;
}

void String::Append(const std::initializer_list<char> inList)
{
	uint32_t newTotalSize = m_size + inList.size();
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, m_size);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}

	memcpy(Large.m_data + m_size, inList.begin(), inList.size());
	Large.m_data[newTotalSize] = '\0';
	m_size = newTotalSize;
}

void String::Replace(uint32 idx, uint32 count, uint32 inCountToInsert, char c)
{
	if (count == 0)
	{
		Insert(idx, inCountToInsert, c);
		return;
	}

	uint32_t newTotalSize = m_size - count + inCountToInsert;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inCountToInsert, Large.m_data + idx + count, m_size - idx - count + 1);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	else
	{
		memmove(Large.m_data + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);
	}

	memset(Large.m_data + idx, c, inCountToInsert);
	m_size = newTotalSize;
}

void String::Replace(uint32 idx, uint32 count, const char* inStr, uint32 inCountToInsert)
{
	if (idx == m_size)
	{
		Append(inStr, inCountToInsert);
		return;
	}

	if (inCountToInsert == UINT32_MAX)
	{
		inCountToInsert = strlen(inStr);
	}

	uint32 newTotalSize = m_size + inCountToInsert - count;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	else
	{
		memmove(Large.m_data + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);
	}
	memcpy(Large.m_data + idx, inStr, inCountToInsert);
	m_size = newTotalSize;
}

void String::Replace(uint32 idx, uint32 count, const String& inStr, uint32 inPos, uint32 inCountToInsert)
{
	if (idx == m_size)
	{
		Append(inStr, inPos, inCountToInsert);
		return;
	}

	if (inCountToInsert == UINT32_MAX)
	{
		inCountToInsert = inStr.Size() - inPos;
	}

	uint32 newTotalSize = m_size + inCountToInsert - count;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	else
	{
		memmove(Large.m_data + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);
	}
	memcpy(Large.m_data + idx, inStr.Data(), inCountToInsert);
	m_size = newTotalSize;
}

void String::Replace(uint32 idx, uint32 count, const StringView inStr, uint32 inPos, uint32 inCountToInsert)
{
	if (idx == m_size)
	{
		Append(inStr, inPos, inCountToInsert);
		return;
	}

	if (inCountToInsert == UINT32_MAX)
	{
		inCountToInsert = inStr.Size() - inPos;
	}

	uint32 newTotalSize = m_size + inCountToInsert - count;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	else
	{
		memmove(Large.m_data + idx + inCountToInsert, Large.m_data + idx + count,
			m_size - idx - count + 1);
	}
	memcpy(Large.m_data + idx, inStr.Data(), inCountToInsert);
	m_size = newTotalSize;
}

void String::Replace(uint32 idx, uint32 count, const std::initializer_list<char> inList)
{
	if (idx == m_size)
	{
		Append(inList);
		return;
	}

	uint32 newTotalSize = m_size + inList.size() - count;
	if (newTotalSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[newTotalSize + 1];

		memcpy(newData, Large.m_data, idx);
		memmove(newData + idx + inList.size(), Large.m_data + idx + count,
			m_size - idx - count + 1);

		free(Large.m_data);
		Large.m_data = newData;
		Large.m_capacity = newTotalSize;
	}
	else
	{
		memmove(Large.m_data + idx + inList.size(), Large.m_data + idx + count,
			m_size - idx - count + 1);
	}

	memcpy(Large.m_data + idx, inList.begin(), inList.size());
	m_size = newTotalSize;
}

void String::Erase(uint32 idx, uint32 inCount)
{
	memmove(Large.m_data + idx, Large.m_data + idx + inCount,
		m_size - idx - inCount + 1);
	m_size = m_size - inCount;
}

void String::PushBack(char c)
{
	uint32 inFutureSize = m_size + 1;
	if (inFutureSize > Large.m_capacity)
	{
		// @todo faut pas faire un new parce que le new il alloue et initialized et nous on veut que allouer used malloc pour juste allouer
		char* newData = new char[inFutureSize];

		memcpy(newData, Large.m_data, m_size);
		newData[m_size] = c;

		free(Large.m_data);

		Large.m_data = newData;
		Large.m_capacity = inFutureSize;
	}
	else
	{
		memset(Large.m_data + m_size, c, 1);
	}

	Large.m_data[inFutureSize] = '\0';
	m_size = inFutureSize;
}

void String::PopBack()
{
	Large.m_data[m_size - 1] = '\0';
	m_size--;
}

String String::GetSubString(uint32 inPos, uint32 inSize) const&
{
	return { *this, inPos, inSize };
}

String String::GetSubString(uint32 inPos, uint32 inSize)&&
{
	return { static_cast<String&&>(*this), inPos, inSize };
}

int32_t String::Compare(const String& inStr) const
{
	uint32_t smallestSize = m_size < inStr.Size() ? m_size : inStr.Size();
	int32_t  res = strncmp(Large.m_data, inStr.Data(), smallestSize);

	if (res == 0)
	{
		if (m_size < inStr.Size())
		{
			return -1;
		}
		else if (m_size > inStr.Size())
		{
			return 1;
		}
	}
	return res;
}

int32_t String::Compare(StringView inStr) const
{
	uint32_t smallestSize = m_size < inStr.Size() ? m_size : inStr.Size();
	int32_t  res = strncmp(Large.m_data, inStr.Data(), smallestSize);

	if (res == 0)
	{
		if (m_size < inStr.Size())
		{
			return -1;
		}
		else if (m_size > inStr.Size())
		{
			return 1;
		}
	}
	return res;
}

int32_t String::Compare(const char* inStr) const
{
	uint32 inStrSize = strlen(inStr);
	uint32_t smallestSize = m_size < inStrSize ? m_size : inStrSize;
	int32_t  res = strncmp(Large.m_data, inStr, smallestSize);

	if (res == 0)
	{
		if (m_size < inStrSize)
		{
			return -1;
		}
		else if (m_size > inStrSize)
		{
			return 1;
		}
	}
	return res;
}

bool String::StartsWith(const String& inStr) const
{
	return strncmp(Large.m_data, inStr.Data(), inStr.Size()) == 0;
}

bool String::StartsWith(StringView inStr) const
{
	return strncmp(Large.m_data, inStr.Data(), inStr.Size()) == 0;
}

bool String::StartsWith(const char* inStr) const
{
	uint32_t len = strlen(inStr);
	return strncmp(Large.m_data, inStr, len) == 0;
}

bool String::StartsWith(char c) const
{
	return Large.m_data[0] == c;
}

bool String::EndsWith(const String& inStr) const
{
	return strncmp(Large.m_data + m_size - inStr.Size(), inStr.Data(), inStr.Size()) == 0;
}

bool String::EndsWith(StringView inStr) const
{
	return strncmp(Large.m_data + m_size - inStr.Size(), inStr.Data(), inStr.Size()) == 0;
}

bool String::EndsWith(const char* inStr) const
{
	uint32_t len = strlen(inStr);
	return strncmp(Large.m_data + m_size - len, inStr, len) == 0;
}

bool String::EndsWith(char c) const
{
	return Large.m_data[m_size - 1] == c;
}

bool String::Contains(const String& inStr) const
{
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = 0; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStr.Size() - nbMatches > m_size)
		{
			return false;
		}

		if (Large.m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStr.Size())
			{
				return true;
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return false;
}

bool String::Contains(StringView inStr) const
{
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = 0; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStr.Size() - nbMatches > m_size)
		{
			return false;
		}

		if (Large.m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStr.Size())
			{
				return true;
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return false;
}

bool String::Contains(const char* inStr) const
{
	uint32 inStrSize = strlen(inStr);
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = 0; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStrSize - nbMatches > m_size)
		{
			return false;
		}

		if (Large.m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStrSize)
			{
				return true;
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return false;
}

bool String::Contains(char c) const
{
	for (uint32_t i = 0; i < m_size; ++i)
	{
		if (Large.m_data[i] == c)
		{
			return true;
		}
	}
	return false;
}

uint32 String::Find(const String& inStr, uint32 inIndex) const
{
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = inIndex; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStr.Size() - nbMatches > m_size)
		{
			return UINT32_MAX;
		}

		if (Large.m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStr.Size())
			{
				return index - (inStr.Size() - 1);
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return UINT32_MAX;
}

uint32 String::Find(StringView inStr, uint32 inIndex) const
{
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = inIndex; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStr.Size() - nbMatches > m_size)
		{
			return UINT32_MAX;
		}

		if (Large.m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStr.Size())
			{
				return index - (inStr.Size() - 1);
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return UINT32_MAX;
}

uint32 String::Find(const char* inStr, uint32 inIndex) const
{
	uint32 inStrSize = strlen(inStr);

	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = inIndex; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStrSize - nbMatches > m_size)
		{
			return UINT32_MAX;
		}

		if (Large.m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStrSize)
			{
				return index - (inStrSize - 1);
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return UINT32_MAX;
}

uint32 String::Find(char c, uint32 inIndex) const
{
	for (uint32_t i = inIndex; i < m_size; ++i)
	{
		if (Large.m_data[i] == c)
		{
			return i;
		}
	}
	return UINT32_MAX;
}