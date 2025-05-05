#pragma once

#include "Core.h"
#include "Assert.h"
#include <utility>

// @todo remove "m_" and put "in" in function parameter 

template <typename taType>
struct DynamicArray
{
	constexpr DynamicArray() = default;
	~DynamicArray();

	DynamicArray(DynamicArray&& ioOther);
	DynamicArray(const DynamicArray& inOther);

	DynamicArray& operator=(DynamicArray&& ioOther);
	DynamicArray& operator=(const DynamicArray& inOther);

	int Size() const { return m_size; }
	int Capacity() const { return m_capacity; }
	bool IsEmpty() const { return m_size == 0; }

	constexpr taType* GetData() { return m_data; };

	// Used that for iterator iteration. "m_data + m_size" return the first invalid pointer after the array
	constexpr taType* End() { return m_data + m_size; }
	constexpr taType* Begin() { return m_data; }
	constexpr taType* end() { return m_data + m_size; }
	constexpr taType* begin() { return m_data; }

	constexpr taType& operator[](int inIndex) const
	{ 
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex]; 
	}
	constexpr taType const& operator[](int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex];
	}

	void Clear();
	void FreeMemory();

	constexpr taType* Front() const { return m_data; }
	constexpr taType* Back() const { return m_data + m_size-1; }
	
	constexpr taType* GetElement(int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex];
	}

	void Reserve(int inCapacity);
/*
	Resize

	Insert 
	Insert
	Insert
	Emplace

	Clear
	FreeMemory
	swapErase
	Erase
	Erase

	pushback
	pushback
	emplaceback
	popback

private:
	MoveFrom
	CopyFrom
	Grow
	MoveElementsBackward
	MoveElementsForward*/

	taType* m_data = nullptr;
	int m_size = 0;
	int m_capacity = 0;
};

// @todo maybe put this in inline file ?
template<typename taType>
DynamicArray<taType>::~DynamicArray()
{
	Clear();
	FreeMemory();
}

template<typename taType>
DynamicArray<taType>::DynamicArray(const DynamicArray& inOther)
{
	m_data = inOther.m_data;
	m_size = inOther.m_size;
	m_capacity = inOther.m_capacity;
}

template<typename taType>
DynamicArray<taType>::DynamicArray(DynamicArray&& inOther)
{
	m_data = std::move(inOther.m_data);
	m_size = std::move(inOther.m_size);
	m_capacity = std::move(inOther.m_capacity);
}

template<typename taType>
DynamicArray<taType>& DynamicArray<taType>::operator=(DynamicArray&& inOther)
{
	m_data = std::move(inOther.m_data);
	m_size = std::move(inOther.m_size);
	m_capacity = std::move(inOther.m_capacity);
	return *this;
}

template<typename taType>
DynamicArray<taType>& DynamicArray<taType>::operator=(const DynamicArray& inOther)
{
	m_data = inOther.m_data;
	m_size = inOther.m_size;
	m_capacity = inOther.m_capacity;
	return *this;
}

template<typename taType>
void DynamicArray<taType>::Clear()
{
	m_data = nullptr;
}

template<typename taType>
void DynamicArray<taType>::FreeMemory()
{
	m_size = 0;
	m_capacity = 0;
	free(m_data);
}

template<typename taType>
void DynamicArray<taType>::Reserve(int inCapacity)
{
	m_capacity = inCapacity;
	m_data = reinterpret_cast<taType**>(realloc(m_data,
		sizeof(taType*) * m_capacity));
}
