#include "Sender.h"

//---------------------------------------------------------------------------------------------
//   class constructor
//
Sender::Sender(Vector2f lCoord, unsigned int direction)
: DirectedObject(lCoord, direction)
{
	numberOfPackageSent = 0;
	maxPackageNumber = 0;
}

//---------------------------------------------------------------------------------------------
//   set max package number
//
void Sender::setMaxPackageNumber(int _maxPackageNumber)
{
	maxPackageNumber = _maxPackageNumber;
}

//---------------------------------------------------------------------------------------------
//   get max package number
//
int Sender::getMaxPackageNumber()
{
	return maxPackageNumber;
}

//---------------------------------------------------------------------------------------------
//   get current number of package sent
//
int Sender::getCurrentNumberOfPackageSent()
{
	return numberOfPackageSent;
}

//---------------------------------------------------------------------------------------------
//   get send time
//
int Sender::getSendTime()
{
	return sendTime;
}

void Sender::setSendTime(int _sendTime)
{
	sendTime = _sendTime;
}

//---------------------------------------------------------------------------------------------
//   send new package
//
Package* Sender::sendNewPackage(unsigned int textureID, int request)
{
	Package *temp = new Package(logicalCoordinate, textureID, dir, request);
	numberOfPackageSent++;

	return temp;
}

//---------------------------------------------------------------------------------------------
//   reduce current number of package sent (called when a package comes to target)
//
void Sender::reduceCurrentNumberOfPackageSent()
{
	numberOfPackageSent--;
}