#pragma once
#include "Vec2.h"
#include <algorithm>


template < typename T >
class _Rect
{
public:
	_Rect() {}
	_Rect(T top, T bottom, T left, T right)
		:
		top(top),
		bottom(bottom),
		left(left),
		right(right)
	{}
	_Rect(const _Rect& rect)
		:
		top(rect.top),
		bottom(rect.bottom),
		left(rect.left),
		right(rect.right)
	{}
	_Rect(_Vec2<T> p0, _Vec2<T> p1)
		:
		_Rect(min(p0.y, p1.y),
			max(p0.y, p1.y),
			min(p0.x, p1.x),
			max(p0.x, p1.x))
	{}
	void Translate(_Vec2<T> d)
	{
		Translate(d.x, d.y);
	}
	void Translate(T dx, T dy)
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	template <typename T2>
	operator _Rect<T2>() const
	{
		return { (T2)top,(T2)bottom,(T2)left,(T2)right };
	}
	void ClipTo(const _Rect& rect)
	{
		top = std::max(top, rect.top);
		bottom = std::min(bottom, rect.bottom);
		left = std::max(left, rect.left);
		right = std::min(right, rect.right);
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
	bool Overlaps(const _Rect& rect) const
	{
		return top < rect.bottom && bottom > rect.top &&
			left < rect.right && right > rect.left;
	}
	template <typename T2>
	bool Contains(_Vec2<T2> p) const
	{
		return p.y >= top && p.y <= bottom && p.x >= left && p.x <= right;
	}
	template <typename T2>
	bool Contains(_Rect<T2> p) const
	{
		return p.top >= top && p.bottom <= bottom && p.left >= left && p.right <= right;
	}
public:
	T top;
	T bottom;
	T left;
	T right;
};

using RectI = _Rect<int>;
using RectF = _Rect<float>;