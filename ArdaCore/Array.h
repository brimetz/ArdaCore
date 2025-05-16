#pragma once

#include "Assert.h"

// List of elements
template <typename DataType, int Size>
struct Array
{
	constexpr static int GetSize() { return Size; }
	constexpr DataType* Data() { return data; }

	// Used that for iterator iteration. "m_data + m_size" return the first invalid pointer after the array
	constexpr const DataType* End() const { return data + Size; }
	constexpr const DataType* Begin() const { return data; }
	constexpr const DataType* end() const { return data + Size; }
	constexpr const DataType* begin() const { return data; }
	constexpr DataType* End() { return data + Size; }
	constexpr DataType* Begin() { return data; }
	constexpr DataType* end() { return data + Size; }
	constexpr DataType* begin() { return data; }

	constexpr DataType& operator[](int inIndex)
	{
		Assert(inIndex >= 0 && inIndex < Size)
		return data[inIndex];
	}

	constexpr DataType const& operator[](int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < Size)
		return data[inIndex];
	}

	void FillArray(const DataType& inValue)
	{
		for (DataType& element : data)
		{
			element = inValue;
		}
	}

	DataType data[Size];
};