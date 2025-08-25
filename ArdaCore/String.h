#pragma once

#include <ArdaCore/Core.h>
#include <ArdaCore/StringView.h>

#include <cstdint>

struct String
{
	String();
	String(uint32 inCount, char c);
	String(const char* inStr, uint32 inCount = UINT32_MAX);
	String(StringView inStr, uint32 inPos = 0, uint32 inCount = UINT32_MAX);
	String(const String& inStr, uint32 inPos = 0, uint32 inCount = UINT32_MAX);
	String(String&& inStr, uint32 inPos = 0, uint32 inCount = UINT32_MAX);
	String(const std::initializer_list<char> inlist);
	~String();

	String& operator=(const char* inStr);
	String& operator=(StringView inStr);
	String& operator=(const String& inStr);
	String& operator=(String&& inStr);
	String& operator=(std::initializer_list<char> inList);

	String& operator+=(const char* inStr);
	String& operator+=(StringView inStr);
	String& operator+=(const String& inStr);
	String& operator+=(std::initializer_list<char> inlist);

	bool operator==(const String& inStr) const;
	bool operator==(StringView inStr) const;
	bool operator==(const char* inStr) const;

	char& operator[](uint32 inPos)&;
	char const& operator[](uint32 inPos) const&;

	bool        IsEmpty() const { return m_size == 0; }
	uint32    Size() const { return m_size; }
	uint32    Capacity() const { return Large.m_capacity; }
	char* Data() { return Large.m_data; }
	const char* Data() const { return Large.m_data; }

	char& Front()& { return Large.m_data[0]; }
	const char& Front() const& { return Large.m_data[0]; }
	char& Back()& { return Large.m_data[m_size]; }
	const char& Back() const& { return Large.m_data[m_size]; }

	void Clear();
	void Reserve(uint32 inCapacity);
	void ShrinkToFit();

	void Resize(uint32 inSize, char c = '\0');

	void Insert(uint32 inIndex, uint32 inCount, char c);
	void Insert(uint32 inIndex, const char* inStr, uint32 inCount = UINT32_MAX);
	void Insert(uint32 inIndex, const String& inStr, uint32 inPos = 0, uint32 inCount = UINT32_MAX);
	void Insert(uint32 inIndex, const StringView inStr, uint32 inPos = 0, uint32 inCount = UINT32_MAX);
	void Insert(uint32 inIndex, const std::initializer_list<char> inList);

	void Append(uint32 inCount, char c);
	void Append(const char* inStr, uint32_t inCount = UINT32_MAX);
	void Append(const String& inStr, uint32_t inPos = 0, uint32_t inCount = UINT32_MAX);
	void Append(const StringView inStr, uint32_t inPos = 0, uint32_t inCount = UINT32_MAX);
	void Append(const std::initializer_list<char> inList);

	void Replace(uint32 inIndex, uint32 inCountToReplace, uint32 inCountToInsert, char c);
	void Replace(uint32 inIndex, uint32 inCountToReplace, const char* inStr,
		uint32 inCountToInsert = UINT32_MAX);
	void Replace(uint32 inIndex, uint32 inCountToReplace, const String& inStr, uint32 inPos = 0,
		uint32 inCountToInsert = UINT32_MAX);
	void Replace(uint32 inIndex, uint32 inCountToReplace, const StringView inStr,
		uint32 inPos = 0, uint32 inCountToInsert = UINT32_MAX);
	void Replace(uint32 inIndex, uint32 inCountToReplace, const std::initializer_list<char> inList);

	void Erase(uint32 inIndex, uint32 inCount = 1);

	void PushBack(char c);
	void PopBack();

	String GetSubString(uint32 inPos, uint32 inSize = UINT32_MAX) const&;
	String GetSubString(uint32 inPos, uint32 inSize = UINT32_MAX)&&;

	int32_t Compare(const String& inStr) const;
	int32_t Compare(StringView inStr) const;
	int32_t Compare(const char* inStr) const;

	bool StartsWith(const String& inStr) const;
	bool StartsWith(StringView inStr) const;
	bool StartsWith(const char* inStr) const;
	bool StartsWith(char c) const;

	bool EndsWith(const String& inStr) const;
	bool EndsWith(StringView inStr) const;
	bool EndsWith(const char* inStr) const;
	bool EndsWith(char c) const;

	bool Contains(const String& inStr) const;
	bool Contains(StringView inStr) const;
	bool Contains(const char* inStr) const;
	bool Contains(char c) const;

	// @todo code is similar to StringView find, maybe find a way to herite String from StringView
	uint32 Find(const String& inStr, uint32 inIndex = 0) const;
	uint32 Find(StringView inStr, uint32 inIndex = 0) const;
	uint32 Find(const char* inStr, uint32 inIndex = 0) const;
	uint32 Find(char c, uint32 inIndex = 0) const;

	// We don't want rvalue to access this function
	//const char* Data() const&& = delete;
	const char& operator[](uint32 inPos) const&& = delete;
	const char& Front() const&& = delete;
	const char& Back() const&& = delete;

private:
	// @todo Add SSO optimisation
	struct
	{
		char* m_data{ nullptr };
		uint32_t m_capacity{ 0 };
	} Large;

	uint32 m_size = 0;
};