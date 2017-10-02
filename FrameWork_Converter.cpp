#include "FrameWork.h"

using FrameWork::Converter;

Converter* Converter::singleton = NULL;
Matrix <float>* Converter::transformMatrix = NULL;

void Converter::fwc_initialize()
{
	/*	Create the convert matrix for fwc_graphicCoordToLogicCoord*/
	Vector2f _original, _topLeft, _botRight;

	_original(MAP_HORIZONTAL_OFFSET + TEXTURE_HEIGHT, MAP_VERTICAL_OFFSET);
	_topLeft(MAP_HORIZONTAL_OFFSET - (MAP_SQR_Y_DIMENSIONS - 1) * TEXTURE_WIDTH / 2.0, MAP_VERTICAL_OFFSET + MAP_SQR_Y_DIMENSIONS * TEXTURE_HEIGHT / 2.0);
	_botRight(MAP_HORIZONTAL_OFFSET + (MAP_SQR_X_DIMENSIONS + 1) * TEXTURE_WIDTH / 2.0, MAP_VERTICAL_OFFSET + MAP_SQR_X_DIMENSIONS * TEXTURE_HEIGHT / 2.0);

	Matrix <float> tmpMatrix_1(3, 3);
	Matrix <float> tmpMatrix_2(3, 3);

	float const data_1[3 * 3] =
	{
		_original.getX(), _botRight.getX(), _topLeft.getX(),
		_original.getY(), _botRight.getY(), _topLeft.getY(),
		1, 1, 1
	};

	float const data_2[3 * 3] =
	{
		0, MAP_SQR_X_DIMENSIONS, 0,
		0, 0, MAP_SQR_Y_DIMENSIONS,
		1, 1, 1
	};

	tmpMatrix_1 = data_1;
	tmpMatrix_2 = data_2;

	transformMatrix = new Matrix <float>(3, 3);

	*transformMatrix = tmpMatrix_2 * (tmpMatrix_1.getInverse());
}

Vector2f Converter::fwc_graphicCoordToLogicCoord(Vector2i grpCoord)
{
	/*  This is very amazing!!! Very difficult problem solved easily using transform matrix  */
	/*  special thank to: http://stackoverflow.com/questions/10716378/pixel-coordinates-on-diamond    */

	static float a = transformMatrix->get(0, 0),
		b = transformMatrix->get(0, 1),
		c = transformMatrix->get(0, 2),
		d = transformMatrix->get(1, 0),
		e = transformMatrix->get(1, 1),
		f = transformMatrix->get(1, 2);

	float lgcCoordX = a * grpCoord.getX() + b * grpCoord.getY() + c;
	float lgcCoordY = d * grpCoord.getX() + e * grpCoord.getY() + f;
	return Vector2f(lgcCoordX, lgcCoordY);
}

Vector2i Converter::fwc_logicCoordToGraphicCoord(Vector2f lgcCoord)
{ 
	float i = lgcCoord.getX();
	float j = lgcCoord.getY();
	return Vector2i ((int)((i - j) * SQUARE_WIDTH / 2 + MAP_HORIZONTAL_OFFSET),
				(int)((i + j) * SQUARE_HEIGHT / 2 + MAP_VERTICAL_OFFSET));
}

void Converter::fwc_destroy()
{
	transformMatrix->~Matrix();
	delete singleton;
}