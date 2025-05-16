#pragma once

#include "Core.h"
#include "Assert.h"
#include <utility>
#include <new>

template <typename DataType>
struct DynamicArray
{
	constexpr DynamicArray() = default;
	~DynamicArray();

	DynamicArray(DynamicArray&& inOther);
	DynamicArray(DynamicArray const& inOther);
	DynamicArray(const std::initializer_list<DataType> inInitializerList);

	DynamicArray& operator=(DynamicArray&& inOther);
	DynamicArray& operator=(DynamicArray const& inOther);
	DynamicArray& operator=(const std::initializer_list<DataType> inInitializerList);

	int Size() const { return m_size; }
	int Capacity() const { return m_capacity; }
	bool IsEmpty() const { return m_size == 0; }

	constexpr DataType* GetData() { return m_data; };

	// Used that for iterator iteration. "m_data + m_size" return the first invalid pointer after the array
	constexpr DataType* End() { return m_data + m_size; }
	constexpr DataType* Begin() { return m_data; }
	constexpr DataType* end() { return m_data + m_size; }
	constexpr DataType* begin() { return m_data; }
	constexpr const DataType* End() const { return m_data + m_size; }
	constexpr const DataType* Begin() const { return m_data; }
	constexpr const DataType* end() const { return m_data + m_size; }
	constexpr const DataType* begin() const { return m_data; }

	constexpr DataType& operator[](int inIndex)
	{ 
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex]; 
	}
	constexpr DataType const& operator[](int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex];
	}

	void Clear();
	void FreeMemory();

	constexpr DataType* Front() const { return m_data; }
	constexpr DataType* Back() const { return m_data + m_size-1; }
	
	constexpr DataType* GetElement(int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex];
	}

	// Manage Capacity
	void Reserve(int inCapacity);
	void Resize(int inCapacity);
	void Resize(int inNewSize, DataType const& inBaseValue);

	// Add element
	void Insert(int inPosition, DataType const& inValue);
	void Insert(int inPosition, DataType&& inValue);

	// @todo Emplace take variadic argument
	//void Emplace(int inPosition, const DataType& inValue);

	void Erase(int inPosition);

	void PushBack(const DataType& inValue);
	void PushBack(DataType&& inValue);
	void PopBack();

private:
	DataType* m_data = nullptr;
	int m_size = 0;
	int m_capacity = 0;
};

template<typename DataType>
DynamicArray<DataType>::~DynamicArray()
{
	Clear();
	FreeMemory();
}

template<typename DataType>
DynamicArray<DataType>::DynamicArray(DynamicArray const& inOther)
{
	Reserve(inOther.m_size);
	m_size = inOther.m_size;

	for (int index = 0; index < inOther.m_size; index++)
	{
		new (m_data+index) DataType(inOther.m_data[index]);
	}
}

template<typename DataType>
DynamicArray<DataType>::DynamicArray(DynamicArray&& inOther)
{
	m_data = std::move(inOther.m_data);
	m_size = std::move(inOther.m_size);
	m_capacity = std::move(inOther.m_capacity);

	inOther.FreeMemory();
}

template<typename DataType>
DynamicArray<DataType>::DynamicArray(const std::initializer_list<DataType> inInitializerList)
{
	Reserve(inInitializerList.size());

	for (const DataType& value : inInitializerList)
	{
		PushBack(value);
	}
}

template<typename DataType>
DynamicArray<DataType>& DynamicArray<DataType>::operator=(DynamicArray&& inOther)
{
	m_data = std::move(inOther.m_data);
	m_size = std::move(inOther.m_size);
	m_capacity = std::move(inOther.m_capacity);

	inOther.m_size = 0;
	inOther.m_capacity = 0;
	inOther.m_data = nullptr;

	return *this;
}

template<typename DataType>
DynamicArray<DataType>& DynamicArray<DataType>::operator=(DynamicArray const& inOther)
{
	for (int index = 0; index < m_size; index++)
	{
		m_data[index].~DataType();
	}

	Reserve(inOther.m_size);

	for (int index = 0; index < inOther.m_size; index++)
	{
		new (m_data + index) DataType(inOther.m_data[index]);
	}

	m_size = inOther.m_size;
	return *this;
}

template<typename DataType>
DynamicArray<DataType>& DynamicArray<DataType>::operator=(const std::initializer_list<DataType> inInitializerList)
{
	for (int index = 0; index < m_size; index++)
	{
		m_data[index].~DataType();
	}
	m_size = 0;
	
	Reserve(inInitializerList.size());

	for (const DataType& value : inInitializerList)
	{
		PushBack(value);
	}

	return *this;
}

template<typename DataType>
void DynamicArray<DataType>::Clear()
{
	for (int index = 0; index < m_size; index++)
	{
		m_data[index].~DataType();
	}
	m_size = 0;
}

template<typename DataType>
void DynamicArray<DataType>::FreeMemory()
{
	m_size = 0;
	m_capacity = 0;
	free(m_data);
}

template<typename DataType>
void DynamicArray<DataType>::Reserve(int inCapacity)
{
	if (m_capacity > inCapacity)
	{
		return;
	}

	m_capacity = inCapacity;

	// Other Solution
	// @todo Jeremie laumon has a TryRealloc to skip the copy sometime, TryRealloc give a bool to know if the allocation was possible
	// in this case, we don't have to copy and free the old buffer
	DataType* newData = (DataType*)malloc(sizeof(DataType) * (m_capacity));
	
	for (int index = 0; index < m_size; index++)
	{
		newData[index] = std::move(m_data[index]);
		m_data[index].~DataType();
	}
	free(m_data);
	m_data = newData;
}

template<typename DataType>
void DynamicArray<DataType>::Resize(int inNewSize)
{
	if (inNewSize == m_size)
	{
		return;
	}

	if (inNewSize < m_size)
	{
		// need to shrink the array
		for (uint32 index = inNewSize; index < m_size; index++)
		{
			m_data[index].~DataType();
		}
	}
	else
	{
		// Need to allocate more memory
		Reserve(inNewSize);
		for (uint32 index = m_size; index < inNewSize; index++)
		{
			new (m_data + index) DataType();
		}
	}

	m_size = inNewSize;
}

template<typename DataType>
void DynamicArray<DataType>::Resize(int inNewSize, DataType const& inBaseValue)
{
	if (inNewSize == m_size)
	{
		return;
	}

	if (inNewSize < m_size)
	{
		// need to shrink the array
		for (uint32 index = inNewSize; index < m_size; index++)
		{
			m_data[index].~DataType();
		}
	}
	else
	{
		// Need to allocate more memory
		Reserve(inNewSize);
		for (uint32 index = m_size; index < inNewSize; index++)
		{
			new (m_data + index) DataType(inBaseValue);
		}
	}

	m_size = inNewSize;
}

template<typename DataType>
void DynamicArray<DataType>::Insert(int inPosition, DataType const& inValue)
{
	if (inPosition == m_size)
	{
		PushBack(inValue);
		return;
	}

	if (m_capacity < m_size + 1)
	{
		m_capacity *= 2;
		DataType* newData = (DataType*)malloc(sizeof(DataType) * (m_capacity));

		for (int index = 0; index < inPosition; index++)
		{
			new (newData + index) DataType(std::move(m_data[index]));
			m_data[index].~DataType();
		}

		new (newData + inPosition) DataType(inValue);

		for (int index = inPosition + 1; index < m_size + 1; index++)
		{
			new (newData + index) DataType(std::move(m_data[index - 1]));
			m_data[index-1].~DataType();
		}

		free(m_data);
		m_data = newData;
	}
	else // No realloc needed
	{
		// Move all elements after the new elements one to the right
		for (int index = m_size; index != inPosition; index--)
		{
			new (m_data + index) DataType(std::move(m_data[index - 1]));
			m_data[index - 1].~DataType();
		}
		new (m_data + inPosition) DataType(inValue);
	}
	m_size += 1;
}

template<typename DataType>
void DynamicArray<DataType>::Insert(int inPosition, DataType&& inValue)
{
	if (inPosition == m_size)
	{
		PushBack(inValue);
		return;
	}

	if (m_capacity < m_size + 1)
	{
		m_capacity *= 2;
		DataType* newData = (DataType*)malloc(sizeof(DataType) * (m_capacity));

		for (int index = 0; index < inPosition; index++)
		{
			new (newData + index) DataType(std::move(m_data[index]));
			m_data[index].~DataType();
		}

		new (newData + inPosition) DataType(std::move(inValue));

		for (int index = inPosition + 1; index < m_size + 1; index++)
		{
			new (newData + index) DataType(std::move(m_data[index - 1]));
			m_data[index - 1].~DataType();
		}

		free(m_data);
		m_data = newData;
	}
	else // No realloc needed
	{
		// Move all elements after the new elements one to the right
		for (int index = m_size; index != inPosition; index--)
		{
			new (m_data + index) DataType(std::move(m_data[index - 1]));
			m_data[index - 1].~DataType();
		}
		new (m_data + inPosition) DataType(std::move(inValue));
	}
	m_size += 1;
}

/*template<typename DataType>
void DynamicArray<DataType>::Emplace(int inPosition, const DataType& inValue)
{
	if (inPosition == m_size)
	{
		PushBack(inValue);
		return;
	}

	if (m_capacity < m_size + 1)
	{
		m_capacity *= 2;
		DataType* newdata = new DataType[m_capacity];

		for (int index = 0; index < inPosition; index++)
		{
			newdata[index] = m_data[index];
			m_data[index].~DataType();
		}

		newdata[inPosition] = inValue;

		for (int index = inPosition + 1; index < m_size + 1; index++)
		{
			newdata[index] = m_data[index - 1];
			m_data[index - 1].~DataType();
		}

		free(m_data);
		m_data = newdata;
	}
	else // No realloc needed
	{
		// Move all elements after the new elements one to the right
		for (int index = m_size; index != inPosition; index--)
		{
			m_data[index] = std::move(m_data[index - 1]);
		}
		m_data[inPosition] = inValue;
	}
	m_size += 1;
}*/

template<typename DataType>
void DynamicArray<DataType>::Erase(int inPosition)
{
	Assert(inPosition < m_size);

	if (inPosition == m_size - 1)
	{
		PopBack();
		return;
	}

	for (int index = inPosition; index < m_size - 1; index++)
	{
		m_data[index].~DataType();
		new (m_data + index) DataType(std::move(m_data[index + 1]));
	}
	m_data[m_size-1].~DataType();
	m_size--;
}

template<typename DataType>
void DynamicArray<DataType>::PushBack(const DataType& inValue)
{
	if (m_capacity < m_size + 1)
	{
		if (m_capacity == 0)
		{
			m_capacity = 1;
		}
		// need to allocate more memory
		Reserve(m_capacity * 2);
	}

	new (m_data + m_size) DataType(inValue);
	m_size += 1;
}

template<typename DataType>
void DynamicArray<DataType>::PushBack(DataType&& inValue)
{
	if (m_capacity < m_size + 1)
	{
		if (m_capacity == 0)
		{
			m_capacity = 1;
		}
		// need to allocate more memory
		Reserve(m_capacity * 2);
	}
	
	new (m_data + m_size) DataType(std::move(inValue));
	m_size += 1;
}

template<typename DataType>
void DynamicArray<DataType>::PopBack()
{
	Assert(m_size >= 1);
	m_size--;
	m_data[m_size].~DataType();
}