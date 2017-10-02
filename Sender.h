#ifndef SENDER_H
#define SENDER_H

#include "Package.h"

class Sender : public DirectedObject
{

private:

	int sendTime;

	int numberOfPackageSent;
	int maxPackageNumber;

public:
	Sender() {
		numberOfPackageSent = 0;
		maxPackageNumber = 0;
	}

	Sender(Vector2f lCoord, unsigned int direction);

	int getSendTime();
	void setSendTime(int _sendTime);

	void setMaxPackageNumber(int _maxPackageNumber);
	int getMaxPackageNumber();

	int getCurrentNumberOfPackageSent();
	void reduceCurrentNumberOfPackageSent();

	Package* sendNewPackage(unsigned int textureID, int request);

};

#endif