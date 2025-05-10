#include "StringView.h"
#include <string.h>
#include "Assert.h"

bool StringView::operator==(const StringView& inOther) const
{
	if (m_size != inOther.m_size)
	{
		return false;
	}

	return Contains(inOther);
}

StringView& StringView::operator=(const StringView& inOther)
{
	m_data = inOther.m_data;
	m_size = inOther.m_size;
	return *this;
}

char StringView::operator[](uint32 inIndex)
{
	return m_data[inIndex];
}

void StringView::DeletePrefix(int PrefixLength)
{
	// Start pointer after the deleted Prefix
	m_data += PrefixLength;
	m_size -= PrefixLength;
}

void StringView::DeleteSuffix(int SuffixLength)
{
	// Str need to finish before the Suffix
	m_size -= SuffixLength;
}

bool StringView::StartsWith(StringView inPrefix) const
{
	return GetSubString(0, inPrefix.m_size) == inPrefix;
}

bool StringView::EndsWith(StringView inSuffix) const
{
	if (m_size < inSuffix.m_size)
		return false;

	return GetSubString(m_size - inSuffix.m_size, inSuffix.m_size) == inSuffix;
}

bool StringView::StartsWith(const char c) const
{
	return m_data[0] == c;
}

bool StringView::EndsWith(const char c) const
{
	return m_data[m_size - 1] == c;
}

StringView StringView::GetSubString(int32 inPosition, int32 inCount) const
{
	Assert(inPosition >= 0 && inPosition < m_size);
	Assert(inPosition + inCount >= 0 && inPosition + inCount <= m_size);

	return { m_data + inPosition, inCount };
}

bool StringView::Contains(StringView inOther) const
{
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = 0; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inOther.m_size - nbMatches > m_size)
		{
			return false;
		}

		if (m_data[index] == inOther[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inOther.m_size)
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

bool StringView::Contains(const char c) const
{
	for (int index = 0; index < m_size; index++)
	{
		if (m_data[index] == c)
		{
			return true;
		}
	}
	return false;
}

uint32 StringView::Find(StringView inStr, uint32 inIndex) const
{
	uint32 startMatchIndex = 0;
	uint32 nbMatches = 0;
	for (int index = 0; index < m_size; index++)
	{
		// We can't find the inStr anymore, there is not enough character remaining
		if (inStr.m_size - nbMatches > m_size)
		{
			return -1;
		}

		if (m_data[index] == inStr[nbMatches])
		{
			nbMatches++;
			if (nbMatches == inStr.m_size)
			{
				return index - (inStr.m_size-1);
			}
		}
		else
		{
			nbMatches = 0;
		}
	}
	return -1;
}

uint32 StringView::Find(const char c, uint32 inIndex) const
{
	Assert(inIndex >= 0 && inIndex < m_size);

	for (int32 index = inIndex; index < m_size; index++)
	{
		if (m_data[index] == c)
		{
			return index;
		}
	}
	return -1;
}