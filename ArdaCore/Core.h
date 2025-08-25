#pragma once

// std::move
#include <utility>

// Basic Types
using int8 = signed char;
using uint8 = unsigned char;
using int16 = signed short;
using uint16 = unsigned short;
using int32 = signed int;
using uint32 = unsigned int;
using int64 = signed long long;
using uint64 = unsigned long long;

// Basic functions
template<typename T> constexpr T Min(T inA, T inB)				{ return inA < inB ? inA : inB; }
template<typename T> constexpr T Max(T inA, T inB)				{ return inA > inB ? inA : inB; }
template<typename T> constexpr T Clamp(T Value, T Low, T High)	{ return Value < Low ? Low : Value > High ? High : Value; }

// std::swap
template <typename T>
constexpr void Swap(T& inA, T& inB)
{
	T temp = std::move(inA);
	inA = std::move(inB);
	inB = std::move(temp);
}

// auto with constexpr, it will be solve at compilation
constexpr bool IsContains(const auto& inContainer, const auto& inElement)
{
	for (auto& element : inContainer)
	{
		if (element == inElement)
		{
			return true;
		}
	}

	return false;
}