#pragma once

#include "Core.h"

struct StringView
{
	constexpr StringView() = default;
	constexpr StringView(const StringView&) = default;
	constexpr StringView(StringView&&) = default;
	constexpr StringView(const char* inStr, int inSize) :
		m_data {inStr},
		m_size {inSize}
	{}
	constexpr ~StringView() = default;

	bool IsEmpty() const { return m_size == 0; }
	uint32 Size() const { return m_size; }
	const char* Data() const { return m_data; }

	bool operator==(const StringView& inOther) const;
	StringView& operator=(const StringView& inOther);
	char operator[](uint32 inIndex);

	char Front() const { return m_data[0]; }
	char Back() const { return m_data[m_size-1]; }

	void DeletePrefix(int PrefixLength);
	void DeleteSuffix(int SuffixLength);

	bool StartsWith(StringView inPrefix) const;
	bool EndsWith(StringView inSuffix) const;
	bool StartsWith(const char c) const;
	bool EndsWith(const char c) const;

	StringView GetSubString(int32 inPosition, int32 inCount) const;

	bool Contains(StringView inOther) const;
	bool Contains(const char c) const;

	uint32 Find(StringView inStr, uint32 inIndex = 0) const;
	uint32 Find(const char c, uint32 inIndex = 0) const;

private:
	const char* m_data = nullptr;
	int m_size = 0;
};