#pragma once

struct Vec2 {
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float len = Length();

		assert(len != 0.f);

		x /= len;
		y /= len;

		return *this;
	}

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator +(Vec2 other)
	{
		return Vec2(x + other.x, y + other.y);
	}

	void operator += (Vec2 other)
	{
		x += other.x;
		y += other.y;
	}

	Vec2 operator -(Vec2 other)
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator *(Vec2 other)
	{
		return Vec2(x * other.x, y * other.y);
	}

	Vec2 operator /(Vec2 other)
	{
		assert(!(0.f == other.x || 0.f == other.y));
		return Vec2(x / other.x, y / other.y);
	}

	Vec2 operator /(float f)
	{
		assert(!(0.f == f));
		return Vec2(x / f, y / f);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};