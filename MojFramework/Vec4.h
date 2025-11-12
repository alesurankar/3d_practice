#pragma once
#include <algorithm>
#include "MyMath.h"
#include "Vec3.h"

template <typename T>
class _Vec4 : public _Vec3<T>
{
public:
	_Vec4() = default;
	_Vec4(T x, T y, T z, T w)
		:
		_Vec3<T>(x, y, z),
		w(w)
    {}
	_Vec4(const _Vec3<T>& v3, float w = 1.0f)
		:
		_Vec3<T>(v3),
		w(w)
    {}
	template <typename T2>
	explicit operator _Vec4<T2>() const
	{
		return{ (T2)this->x,(T2)this->y,(T2)this->z,(T2)w };
	}
	_Vec4 operator-() const
	{
		return _Vec4(-this->x, -this->y, -this->z, -w);
	}
	_Vec4& operator=(const _Vec4& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		w = rhs.w;
		return *this;
	}
	_Vec4& operator+=(const _Vec4& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		w += rhs.w;
		return *this;
	}
	_Vec4& operator-=(const _Vec4& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
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
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		w *= rhs;
		return *this;
	}
	_Vec4 operator*(const T& rhs) const
	{
		return _Vec4(*this) *= rhs;
	}
	_Vec4& operator/=(const T& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		w /= rhs;
		return *this;
	}
	_Vec4 operator/(const T& rhs) const
	{
		return _Vec4(*this) /= rhs;
	}
	bool operator==(const _Vec4& rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y && rhs.z == this->z && rhs.w == w;
	}
	bool operator!=(const _Vec4& rhs) const
	{
		return !(*this == rhs);
	}
	// clamp to between 0.0 ~ 1.0
	_Vec4& Saturate()
	{
		this->x = std::min(1.0f, std::max(0.0f, this->x));
		this->y = std::min(1.0f, std::max(0.0f, this->y));
		this->z = std::min(1.0f, std::max(0.0f, this->z));
		w = std::min(1.0f, std::max(0.0f, w));
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
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
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