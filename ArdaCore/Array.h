#pragma once

#include "Assert.h"

// List of elements
template <typename T, int Size>
struct Array
{
	constexpr static int GetSize() { return Size; }
	constexpr T* Data() { return data; }

	// Used that for iterator iteration. "m_data + m_size" return the first invalid pointer after the array
	constexpr T* End() { return data + Size; }
	constexpr T* Begin() { return data; }
	constexpr T* end() { return data + Size; }
	constexpr T* begin() { return data; }

	/*template<typename T>
	Array<T>::Array(const std::initializer_list<T>& inInitializerList)
	{
		Reserve(inInitializerList.size());

		for (const T& value : inInitializerList)
		{
			PushBack(value);
		}
	}*/

	constexpr T& operator[](int index)
	{
		Assert(index >= 0 && index < Size)
		return data[index];
	}

	constexpr T const& operator[](int index) const
	{
		Assert(index >= 0 && index < Size)
		return data[index];
	}

	void FillArray(const T& value)
	{
		for (T& element : data)
		{
			element = value;
		}
	}
//private:
	T data[Size];
};