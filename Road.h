#ifndef ROAD_H
#define ROAD_H

struct sDirection
{
	int isEnable;
	int isIn;
};

class Road
{
private:
	int inNumber, outNumber;
	sDirection direction[4];

public:
	Road()
	{
		inNumber = 0;
		outNumber = 0;
		direction[0].isEnable = false;
		direction[0].isIn = true;
		direction[1].isEnable = false;
		direction[1].isIn = true;
		direction[2].isEnable = false;
		direction[2].isIn = true;
		direction[3].isEnable = false;
		direction[3].isIn = true;
	}

	int get_in_number()
	{
		return inNumber;
	}

	void set_in_number(int in_number)
	{
		this->inNumber = in_number;
	}
	int get_out_number()
	{
		return outNumber;
	}

	void set_out_number(int out_number)
	{
		this->outNumber = out_number;
	}

	sDirection getStructDirection(int dir)
	{
		return direction[dir];
	}

	void setStructDirection(int dir, sDirection structDirection)
	{
		direction[dir] = structDirection;
	}
};
#endif