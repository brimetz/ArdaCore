#pragma once

#include "ArdaCore/Core.h"
#include "ArdaCore/Assert.h"

template <typename DataType>
struct ArrayView
{
	constexpr ArrayView() = default;
	constexpr ArrayView(const ArrayView& inOther) = default;
	constexpr ArrayView(ArrayView&& inOther) = default;

	constexpr bool operator==(ArrayView inOther) const;
	constexpr ArrayView& operator=(const ArrayView& inOther) = default;
	constexpr ArrayView& operator=(ArrayView&& inOther) = default;
	constexpr const DataType& operator[](int inIndex) { return m_data[inIndex]; }

	// https://brevzin.github.io/c++/2020/02/05/constexpr-array-size/
	template<int Size>
	constexpr ArrayView(const DataType(&arr)[Size]) :
		m_data{ arr },
		m_size{ Size }
	{}
	constexpr ArrayView(const DataType* inData, uint32 inSize) :
		m_data{ inData },
		m_size{ inSize }
	{}
	constexpr ArrayView(const std::initializer_list<DataType> inList);

	constexpr bool IsEmpty() const { return m_size == 0; }
	constexpr int Size() const { return m_size; }
	constexpr DataType* Data() const { return m_data; }

	constexpr const DataType* End() const { return m_data + m_size; }
	constexpr const DataType* Begin() const { return m_data; }
	constexpr const DataType* end() const { return m_data + m_size; }
	constexpr const DataType* begin() const { return m_data; }

	constexpr const DataType& Front() const
	{
		Assert(m_size > 0);
		return m_data[0];
	}
	constexpr DataType& Front()
	{
		Assert(m_size > 0);
		return m_data[0];
	}

	constexpr const DataType& Back() const
	{
		Assert(m_size > 0);
		return m_data[m_size-1];
	}
	constexpr DataType& Back()
	{
		Assert(m_size > 0);
		return m_data[m_size-1];
	}

	constexpr ArrayView GetStartTo(uint32 inCount) const;
	constexpr ArrayView GetEndFrom(uint32 inCount) const;
	constexpr ArrayView GetSubArray(int inStartIndex, uint32 inElementsNumber) const;
private:
	const DataType* m_data = nullptr;
	uint32 m_size = 0;
};

template<typename DataType>
constexpr ArrayView<DataType>::ArrayView(const std::initializer_list<DataType> inList) :
	m_data{ inList.begin() },
	m_size{ static_cast<uint32>(inList.size()) }
{}

template<typename DataType>
constexpr bool ArrayView<DataType>::operator==(ArrayView inOther) const
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

template<typename DataType>
constexpr ArrayView<DataType> ArrayView<DataType>::GetStartTo(uint32 inCount) const
{
	Assert(inCount > 0 || inCount < m_size);
	return { m_data, inCount };
}

template<typename DataType>
constexpr ArrayView<DataType> ArrayView<DataType>::GetEndFrom(uint32 inCount) const
{
	Assert(inCount > 0 || inCount < m_size);
	return { m_data + m_size - inCount, inCount };
}

template<typename DataType>
constexpr ArrayView<DataType> ArrayView<DataType>::GetSubArray(int inStartIndex, uint32 inElementsNumber) const
{
	Assert(inStartIndex > 0 || inStartIndex < m_size);
	Assert(inStartIndex + inElementsNumber > 0 || inStartIndex + inElementsNumber < m_size);
	return { m_data + inStartIndex, inElementsNumber };
}