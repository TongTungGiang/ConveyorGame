#include "Receiver.h"

//---------------------------------------------------------------------------------------------
//   class constructor
//
Receiver::Receiver(Vector2f lCoord)
: LogicalObject(lCoord)
{
}

//---------------------------------------------------------------------------------------------
//   get type of receiver
//
bool Receiver::receivedRightPackage(Package package)
{
	timeReceived = FrameWork::Timer::instance()->fwt_getTime();

	if (package.getRequest() == this->receiverTextureID)
		right = true;
	else right = false;

	return right;
}

bool Receiver::receivedRightPackage()
{
	return right;
}

void Receiver::setReceiverTextureID(unsigned int textureID)
{
	receiverTextureID = textureID;
}

unsigned int Receiver::getReceiverTextureID()
{ 
	return receiverTextureID;
}

unsigned int Receiver::getTimeReceived()
{
	return timeReceived;
}