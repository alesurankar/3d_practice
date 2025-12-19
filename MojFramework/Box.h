#pragma once
#include "Vec3.h"

template<typename T>
class Box_
{
public:
    Box_() = default;

    Box_(T left_in, T top_in, T front_in,
        T right_in, T bottom_in, T back_in)
        :
        left(left_in),
        top(top_in),
        front(front_in),
        right(right_in),
        bottom(bottom_in),
        back(back_in)
    {
    }

    Box_(const Vec3& min, const Vec3& max)
        :
        left((T)min.x),
        top((T)min.y),
        front((T)min.z),
        right((T)max.x),
        bottom((T)max.y),
        back((T)max.z)
    {
    }

    bool IsOverlappingWith(const Box_& o) const
    {
        return right >= o.left && left <= o.right &&
            bottom >= o.top && top <= o.bottom &&
            back >= o.front && front <= o.back;
    }

public:
    T left;
    T top;
    T front;
    T right;
    T bottom;
    T back;
};

using BoxF = Box_<float>;
using BoxI = Box_<int>;
