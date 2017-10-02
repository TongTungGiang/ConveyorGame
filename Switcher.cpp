#include "Switcher.h"

//---------------------------------------------------------------------------------------------
//   class constructor
//
Switcher::Switcher(Vector2f lCoord, unsigned int direction)
	: DirectedObject(lCoord, direction)
{
	possibleDirections[NORTH] = false;
	possibleDirections[WEST] = false;
	possibleDirections[SOUTH] = false;
	possibleDirections[EAST] = false;
}

//---------------------------------------------------------------------------------------------
//   set cross point's possible directions
//
void Switcher::setPossibleDirections(int N, int W, int S, int E)
{
	possibleDirections[NORTH] = N;
	possibleDirections[WEST] = W;
	possibleDirections[SOUTH] = S;
	possibleDirections[EAST] = E;
}

//---------------------------------------------------------------------------------------------
//   change direction of cross point to next possible direction
//
int Switcher::changeToNextPossibleDirection()
{
	for (int i = 1; i <= 3; i++)
	{
		if (possibleDirections[(dir + i)% 4])
		{
			dir = (dir + i) % 4;
			break;
		}
	}
	return dir;
}