#pragma once
#include <algorithm>
#include "MyMath.h"
#include "Vec2.h"

template <typename T>
class _Vec3 : public _Vec2<T>
{
public:
    using _Vec2<T>::x;
    using _Vec2<T>::y;
public:
    _Vec3() = default;
    _Vec3(T x, T y, T z)
        :
        _Vec2<T>(x, y),
        z(z)
    {
    }
    _Vec3(const _Vec2<T>& v, T z)
        :
        _Vec3<T>(v.x, v.y, z)
    {
    }
    template <typename T2>
    explicit operator _Vec3<T2>() const
    {
        return { (T2)x, (T2)y, (T2)z };
    }
    T LenSq() const
    {
        return sq(*this);
    }
    T Len() const
    {
        return static_cast<T>(sqrt(LenSq()));
    }
    _Vec3& Normalize()
    {
        const T length = Len();
        x /= length;
        y /= length;
        z /= length;
        return *this;
    }
    _Vec3 GetNormalized() const
    {
        _Vec3 norm = *this;
        norm.Normalize();
        return norm;
    }
    _Vec3 operator-() const
    {
        return _Vec3(-x, -y, -z);
    }
    _Vec3& operator=(const _Vec3& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }
    _Vec3& operator+=(const _Vec3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    _Vec3& operator-=(const _Vec3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    T operator*(const _Vec3& rhs) const // dot product
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    _Vec3 operator+(const _Vec3& rhs) const
    {
        return _Vec3(*this) += rhs;
    }
    _Vec3 operator-(const _Vec3& rhs) const
    {
        return _Vec3(*this) -= rhs;
    }
    _Vec3& operator*=(const T& rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }
    _Vec3 operator*(const T& rhs) const
    {
        return _Vec3(*this) *= rhs;
    }
    _Vec3 operator%(const _Vec3& rhs) const // cross product
    {
        return _Vec3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x);
    }
    _Vec3& operator/=(const T& rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }
    _Vec3 operator/(const T& rhs) const
    {
        return _Vec3(*this) /= rhs;
    }
    bool operator==(const _Vec3& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    bool operator!=(const _Vec3& rhs) const
    {
        return !(*this == rhs);
    }
    _Vec3& Saturate()
    {
        x = std::min(T(1), std::max(T(0), x));
        y = std::min(T(1), std::max(T(0), y));
        z = std::min(T(1), std::max(T(0), z));
        return *this;
    }
    _Vec3 GetSaturated() const
    {
        _Vec3 temp(*this);
        temp.Saturate();
        return temp;
    }
    _Vec3& Hadamard(const _Vec3& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }
    _Vec3 GetHadamard(const _Vec3& rhs) const
    {
        _Vec3 temp(*this);
        temp.Hadamard(rhs);
        return temp;
    }
public:
    T z;
};

using Vec3 = _Vec3<float>;
using Ved3 = _Vec3<double>;
using Vei3 = _Vec3<int>;