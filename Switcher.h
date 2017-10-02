#ifndef SWITCHER_H
#define SWITCHER_H

#include "DirectedObject.h"

class Switcher : public DirectedObject
{

private:

	int possibleDirections[4];

public:

	Switcher() {};

	Switcher(Vector2f lCoord, unsigned int direction);

	void setPossibleDirections(int N, int W, int S, int E);

	void setPossibleDirections(int dir, int tof)
	{
		possibleDirections[dir] = tof;
	}

	void getPossibleDirection(int* N, int* W, int* S, int* E)
	{
		*N = possibleDirections[0];
		*W = possibleDirections[1];
		*S = possibleDirections[2];
		*E = possibleDirections[3];
	}

	int getPossibleDirectionNumber()
	{
		return ((possibleDirections[NORTH] ? 1 : 0) + (possibleDirections[WEST] ? 1 : 0) +
			(possibleDirections[SOUTH] ? 1 : 0) + (possibleDirections[EAST] ? 1 : 0) );
	}

	int changeToNextPossibleDirection();

};

#endif