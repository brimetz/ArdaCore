#pragma once

// Basic Types
using int8 = signed char;
using uint8 = unsigned char;
using int16 = signed short;
using uint16 = unsigned short;
using int32 = signed long;
using uint32 = unsigned long;
using int64 = signed long long;
using uint64 = unsigned long long;

// Basic functions
template<typename T> constexpr T Min(T inA, T inB)				{ return inA < inB ? inA : inB; }
template<typename T> constexpr T Max(T inA, T inB)				{ return inA > inB ? inA : inB; }
template<typename T> constexpr T Clamp(T Value, T Low, T High)	{ return Value < Low ? Low : Value > High ? High : Value; }