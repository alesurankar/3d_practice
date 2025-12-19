#pragma once
#include <algorithm>
#include "MyMath.h"
#include "Vec3.h"

template <typename T>
class _Vec4 : public _Vec3<T>
{
public:
	using _Vec3<T>::x;
	using _Vec3<T>::y;
	using _Vec3<T>::z;
public:
	_Vec4() = default;
	_Vec4(T x, T y, T z, T w)
		:
		_Vec3<T>(x, y, z),
		w(w)
    {}
	_Vec4(const _Vec3<T>& v3, T w = T(1))
		:
		_Vec3<T>(v3),
		w(w)
    {}
	template <typename T2>
	explicit operator _Vec4<T2>() const
	{
		return{ (T2)x,(T2)y,(T2)z,(T2)w };
	}
	_Vec4 operator-() const
	{
		return _Vec4(-x, -y, -z, -w);
	}
	_Vec4& operator+=(const _Vec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}
	_Vec4& operator-=(const _Vec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}
	_Vec4 operator+(const _Vec4& rhs) const
	{
		return _Vec4(*this) += rhs;
	}
	_Vec4 operator-(const _Vec4& rhs) const
	{
		return _Vec4(*this) -= rhs;
	}
	_Vec4& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}
	_Vec4 operator*(const T& rhs) const
	{
		return _Vec4(*this) *= rhs;
	}
	_Vec4& operator/=(const T& rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}
	_Vec4 operator/(const T& rhs) const
	{
		return _Vec4(*this) /= rhs;
	}
	bool operator==(const _Vec4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}
	bool operator!=(const _Vec4& rhs) const
	{
		return !(*this == rhs);
	}
	// clamp to between 0.0 ~ 1.0
	_Vec4& Saturate()
	{
		x = std::min(T(1), std::max(T(0), x));
		y = std::min(T(1), std::max(T(0), y));
		z = std::min(T(1), std::max(T(0), z));
		w = std::min(T(1), std::max(T(0), w));
		return *this;
	}
	_Vec4 GetSaturated() const
	{
		_Vec4 temp(*this);
		temp.Saturate();
		return temp;
	}
	_Vec4& Hadamard(const _Vec4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}
	_Vec4 GetHadamard(const _Vec4& rhs) const
	{
		_Vec4 temp(*this);
		temp.Hadamard(rhs);
		return temp;
	}
public:
	T w;
};

using Vec4 = _Vec4<float>;
using Ved4 = _Vec4<double>;
using Vei4 = _Vec4<int>;