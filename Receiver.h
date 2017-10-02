#ifndef END_POINT_H
#define END_POINT_H

#include "Package.h"

class Receiver : public LogicalObject
{
private:
	unsigned int receiverTextureID;
	unsigned int timeReceived;
	bool right;

public:

	Receiver(Vector2f lCoord);

	void setReceiverTextureID(unsigned int textureID);

	unsigned int getReceiverTextureID();

	bool receivedRightPackage(Package package);

	bool receivedRightPackage();

	unsigned int getTimeReceived();
};

#endif