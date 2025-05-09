#pragma once

#include "Core.h"
#include "Assert.h"
#include <utility>
#include <new>

// @todo remove "m_" and put "in" in function parameter 

template <typename T>
struct DynamicArray
{
	constexpr DynamicArray() = default;
	~DynamicArray();

	DynamicArray(DynamicArray&& ioOther);
	DynamicArray(DynamicArray const& inOther);
	DynamicArray(const std::initializer_list<T>& inInitializerList);

	DynamicArray& operator=(DynamicArray&& ioOther);
	DynamicArray& operator=(DynamicArray const& inOther);
	DynamicArray& operator=(const std::initializer_list<T>& inInitializerList);

	int Size() const { return m_size; }
	int Capacity() const { return m_capacity; }
	bool IsEmpty() const { return m_size == 0; }

	constexpr T* GetData() { return m_data; };

	// Used that for iterator iteration. "m_data + m_size" return the first invalid pointer after the array
	constexpr T* End() { return m_data + m_size; }
	constexpr T* Begin() { return m_data; }
	constexpr T* end() { return m_data + m_size; }
	constexpr T* begin() { return m_data; }
	constexpr const T* End() const { return m_data + m_size; }
	constexpr const T* Begin() const { return m_data; }
	constexpr const T* end() const { return m_data + m_size; }
	constexpr const T* begin() const { return m_data; }

	constexpr T& operator[](int inIndex)
	{ 
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex]; 
	}
	constexpr T const& operator[](int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex];
	}

	void Clear();
	void FreeMemory();

	constexpr T* Front() const { return m_data; }
	constexpr T* Back() const { return m_data + m_size-1; }
	
	constexpr T* GetElement(int inIndex) const
	{
		Assert(inIndex >= 0 && inIndex < m_size)
		return m_data[inIndex];
	}

	// Manage Capacity
	void Reserve(int inCapacity);
	void Resize(int inCapacity);
	void Resize(int inNewSize, T const& inBaseValue);

	// Add element
	void Insert(int inPosition, T const& inValue);
	void Insert(int inPosition, T&& inValue);

	// @todo Emplace take variadic argument
	//void Emplace(int inPosition, const T& inValue);

	void Erase(int inPosition);

	void PushBack(const T& inValue);
	void PushBack(T&& inValue);
	void PopBack();

private:
	T* m_data = nullptr;
	int m_size = 0;
	int m_capacity = 0;
};

template<typename T>
DynamicArray<T>::~DynamicArray()
{
	Clear();
	FreeMemory();
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray const& inOther)
{
	Reserve(inOther.m_size);
	m_size = inOther.m_size;

	for (int index = 0; index < inOther.m_size; index++)
	{
		new (m_data+index) T(inOther.m_data[index]);
	}

}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& inOther)
{
	m_data = std::move(inOther.m_data);
	m_size = std::move(inOther.m_size);
	m_capacity = std::move(inOther.m_capacity);

	inOther.FreeMemory();
}

template<typename T>
DynamicArray<T>::DynamicArray(const std::initializer_list<T>& inInitializerList)
{
	Reserve(inInitializerList.size());

	for (const T& value : inInitializerList)
	{
		PushBack(value);
	}
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& inOther)
{
	m_data = std::move(inOther.m_data);
	m_size = std::move(inOther.m_size);
	m_capacity = std::move(inOther.m_capacity);

	inOther.m_size = 0;
	inOther.m_capacity = 0;
	inOther.m_data = nullptr;

	return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray const& inOther)
{
	for (int index = 0; index < m_size; index++)
	{
		m_data[index].~T();
	}

	Reserve(inOther.m_size);

	for (int index = 0; index < inOther.m_size; index++)
	{
		new (m_data + index) T(inOther.m_data[index]);
	}

	m_size = inOther.m_size;
	return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const std::initializer_list<T>& inInitializerList)
{
	for (int index = 0; index < m_size; index++)
	{
		m_data[index].~T();
	}
	m_size = 0;
	
	Reserve(inInitializerList.size());

	for (const T& value : inInitializerList)
	{
		PushBack(value);
	}

	return *this;
}

template<typename T>
void DynamicArray<T>::Clear()
{
	for (int index = 0; index < m_size; index++)
	{
		m_data[index].~T();
	}
	m_size = 0;
}

template<typename T>
void DynamicArray<T>::FreeMemory()
{
	m_size = 0;
	m_capacity = 0;
	free(m_data);
}

template<typename T>
void DynamicArray<T>::Reserve(int inCapacity)
{
	if (m_capacity > inCapacity)
	{
		return;
	}

	m_capacity = inCapacity;

	// Faire un alloc
	// Copier la data a la main si buffer a changé en memoire
	// Free l'ancien buffer
	// Other Solution
	// @todo Jeremie laumon has a TryRealloc to skip the copy sometime, TryRealloc give a bool to know if the allocation was possible
	// in this case, we don't have to copy and free the old buffer
	T* newdata = new T[m_capacity];
	
	for (int index = 0; index < m_size; index++)
	{
		newdata[index] = std::move(m_data[index]);
		m_data[index].~T();
	}
	free(m_data);
	m_data = newdata;
}

template<typename T>
void DynamicArray<T>::Resize(int inNewSize)
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
			m_data[index].~T();
		}
	}
	else
	{
		// Need to allocate more memory
		Reserve(inNewSize);
		for (uint32 index = m_size; index < inNewSize; index++)
		{
			new (m_data + index) T();
		}
	}

	m_size = inNewSize;
}

template<typename T>
void DynamicArray<T>::Resize(int inNewSize, T const& inBaseValue)
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
			m_data[index].~T();
		}
	}
	else
	{
		// Need to allocate more memory
		Reserve(inNewSize);
		for (uint32 index = m_size; index < inNewSize; index++)
		{
			new (m_data + index) T(inBaseValue);
		}
	}

	m_size = inNewSize;
}

template<typename T>
void DynamicArray<T>::Insert(int inPosition, T const& inValue)
{
	if (inPosition == m_size)
	{
		PushBack(inValue);
		return;
	}

	if (m_capacity < m_size + 1)
	{
		m_capacity *= 2;
		T* newdata = new T[m_capacity];

		for (int index = 0; index < inPosition; index++)
		{
			new (newdata + index) T(std::move(m_data[index]));
			m_data[index].~T();
		}

		new (newdata + inPosition) T(inValue);

		for (int index = inPosition + 1; index < m_size + 1; index++)
		{
			new (newdata + index) T(std::move(m_data[index - 1]));
			m_data[index-1].~T();
		}

		free(m_data);
		m_data = newdata;
	}
	else // No realloc needed
	{
		// Move all elements after the new elements one to the right
		for (int index = m_size; index != inPosition; index--)
		{
			new (m_data + index) T(std::move(m_data[index - 1]));
			m_data[index - 1].~T();
		}
		new (m_data + inPosition) T(inValue);
	}
	m_size += 1;
}

template<typename T>
void DynamicArray<T>::Insert(int inPosition, T&& inValue)
{
	if (inPosition == m_size)
	{
		PushBack(inValue);
		return;
	}

	if (m_capacity < m_size + 1)
	{
		m_capacity *= 2;
		T* newdata = new T[m_capacity];

		for (int index = 0; index < inPosition; index++)
		{
			new (newdata + index) T(std::move(m_data[index]));
			m_data[index].~T();
		}

		new (newdata + inPosition) T(std::move(inValue));

		for (int index = inPosition + 1; index < m_size + 1; index++)
		{
			new (newdata + index) T(std::move(m_data[index - 1]));
			m_data[index - 1].~T();
		}

		free(m_data);
		m_data = newdata;
	}
	else // No realloc needed
	{
		// Move all elements after the new elements one to the right
		for (int index = m_size; index != inPosition; index--)
		{
			new (m_data + index) T(std::move(m_data[index - 1]));
			m_data[index - 1].~T();
		}
		new (m_data + inPosition) T(std::move(inValue));
	}
	m_size += 1;
}

/*template<typename T>
void DynamicArray<T>::Emplace(int inPosition, const T& inValue)
{
	if (inPosition == m_size)
	{
		PushBack(inValue);
		return;
	}

	if (m_capacity < m_size + 1)
	{
		m_capacity *= 2;
		T* newdata = new T[m_capacity];

		for (int index = 0; index < inPosition; index++)
		{
			newdata[index] = m_data[index];
			m_data[index].~T();
		}

		newdata[inPosition] = inValue;

		for (int index = inPosition + 1; index < m_size + 1; index++)
		{
			newdata[index] = m_data[index - 1];
			m_data[index - 1].~T();
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

template<typename T>
void DynamicArray<T>::Erase(int inPosition)
{
	Assert(inPosition < m_size);

	if (inPosition == m_size - 1)
	{
		PopBack();
		return;
	}

	for (int index = inPosition; index < m_size - 1; index++)
	{
		m_data[index].~T();
		new (m_data + index) T(std::move(m_data[index + 1]));
	}
	m_data[m_size-1].~T();
	m_size--;
}

template<typename T>
void DynamicArray<T>::PushBack(const T& inValue)
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

	new (m_data + m_size) T(inValue);
	m_size += 1;
}

template<typename T>
void DynamicArray<T>::PushBack(T&& inValue)
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
	
	new (m_data + m_size) T(std::move(inValue));
	m_size += 1;
}

template<typename T>
void DynamicArray<T>::PopBack()
{
	Assert(m_size >= 1);
	m_size--;
	m_data[m_size].~T();
}