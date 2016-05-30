#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Event.h"
#include "Enemy.h"

using namespace std;

class Room
{
private:
	bool north;
	bool south;
	bool east;
	bool west;
	int room_x;
	int room_y;
public:
	Room();
	Room(int north, int south, int east, int west, int x, int y);
	bool getNorth();
	bool getSouth();
	bool getEast();
	bool getWest();
	void setRoomX(int x);
	void setRoomY(int y);
	int getRoomX();
	int getRoomY();
	void setNorth(bool boolean);
	void setSouth(bool boolean);
	void setEast(bool boolean);
	void setWest(bool boolean);
};

#endif