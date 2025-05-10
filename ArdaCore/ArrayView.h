#pragma once

#include "ArdaCore/Core.h"
#include "ArdaCore/Assert.h"

template <typename T>
struct ArrayView
{
	constexpr ArrayView() = default;
	constexpr ArrayView(const ArrayView& inOther) = default;
	constexpr ArrayView(ArrayView&& inOther) = default;

	constexpr bool operator==(ArrayView inOther) const;
	constexpr ArrayView& operator=(const ArrayView& inOther) = default;
	constexpr ArrayView& operator=(ArrayView&& inOther) = default;
	constexpr const T& operator[](int inIndex) { return m_data[inIndex]; }

	// https://brevzin.github.io/c++/2020/02/05/constexpr-array-size/
	template<int Size>
	constexpr ArrayView(const T(&arr)[Size]) :
		m_data{ arr },
		m_size{ Size }
	{}
	constexpr ArrayView(const T* inData, uint32 inSize) :
		m_data{ inData },
		m_size{ inSize }
	{}
	constexpr ArrayView(const std::initializer_list<T>& inList);

	constexpr bool IsEmpty() const { return m_size == 0; }
	constexpr int Size() const { return m_size; }
	constexpr T* Data() const { return m_data; }

	constexpr const T* End() const { return m_data + m_size; }
	constexpr const T* Begin() const { return m_data; }
	constexpr const T* end() const { return m_data + m_size; }
	constexpr const T* begin() const { return m_data; }

	constexpr const T& Front() const
	{
		Assert(m_size > 0);
		return m_data[0];
	}
	constexpr T& Front()
	{
		Assert(m_size > 0);
		return m_data[0];
	}

	constexpr const T& Back() const
	{
		Assert(m_size > 0);
		return m_data[m_size-1];
	}
	constexpr T& Back()
	{
		Assert(m_size > 0);
		return m_data[m_size-1];
	}

	constexpr ArrayView GetStartTo(uint32 inCount) const;
	constexpr ArrayView GetEndFrom(uint32 inCount) const;
	constexpr ArrayView GetSubArray(int inStartIndex, uint32 inElementsNumber) const;
private:
	const T* m_data = nullptr;
	uint32 m_size = 0;
};

template<typename T>
constexpr ArrayView<T>::ArrayView(const std::initializer_list<T>& inList) :
	m_data{ inList.begin() },
	m_size{ static_cast<uint32>(inList.size()) }
{}

template<typename T>
constexpr bool ArrayView<T>::operator==(ArrayView inOther) const
{
	if (m_size != inOther.Size())
	{
		return false;
	}

	auto currentIt = Begin();
	auto otherIt = inOther.Begin();
	while (currentIt != End())
	{
		if (*currentIt != *otherIt)
			return false;

		++currentIt;
		++otherIt;
	}

	return true;
}

template<typename T>
constexpr ArrayView<T> ArrayView<T>::GetStartTo(uint32 inCount) const
{
	Assert(inCount > 0 || inCount < m_size);
	return { m_data, inCount };
}

template<typename T>
constexpr ArrayView<T> ArrayView<T>::GetEndFrom(uint32 inCount) const
{
	Assert(inCount > 0 || inCount < m_size);
	return { m_data + m_size - inCount, inCount };
}

template<typename T>
constexpr ArrayView<T> ArrayView<T>::GetSubArray(int inStartIndex, uint32 inElementsNumber) const
{
	Assert(inStartIndex > 0 || inStartIndex < m_size);
	Assert(inStartIndex + inElementsNumber > 0 || inStartIndex + inElementsNumber < m_size);
	return { m_data + inStartIndex, inElementsNumber };
}