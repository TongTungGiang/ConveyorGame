#ifndef VECTOR_2
#define VECTOR_2

class Vector2f
{
private:
	float x;
	float y;

public:
	Vector2f() {};

	Vector2f(const float &x, const float &y)
	{
		this->x = x;
		this->y = y;
	}

	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	void setCoordinate(const float &x, const float &y)
	{
		this->x = x;
		this->y = y;
	}
	void operator() (const float &x, const float &y)
	{
		this->x = x;
		this->y = y;
	}

	void operator= (Vector2f other)
	{
		this->x = other.getX();
		this->y = other.getY();
	}

};

class Vector2i
{
private:
	int x;
	int y;

public:
	Vector2i() {}

	Vector2i(const int &x, const int &y)
	{
		this->x = x;
		this->y = y;
	}

	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void setCoordinate(const int &x, const int &y)
	{
		this->x = x;
		this->y = y;
	}
	void operator() (const int &x, const int &y)
	{
		this->x = x;
		this->y = y;
	}
	void operator= (Vector2i other)
	{
		x = other.getX();
		y = other.getY();
	}

};
#endif