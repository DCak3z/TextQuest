#include "Room.h"
#include "EnemyFactory.h"
#include <iostream>

Room::Room()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	room_x = NULL;
	room_y = NULL;
	vector<Event*> roomEvents;
	vector<Character*> participants;
}

Room::Room(int n, int s, int e, int w, int x, int y)
{
	if (n == 0 || n == 1)
	{
		north = false;
	}
	else
	{
		north = true;
	}
	if (s == 0 || s == 1)
	{
		south = false;
	}
	else
	{
		south = true;
	}
	if (e == 0 || e == 1)
	{
		east = false;
	}
	else
	{
		east = true;
	}
	if (w == 0 || w == 1)
	{
		west = false;
	}
	else
	{
		west = true;
	}
	room_x = x;
	room_y = y;

	//Adds random number of enemies (between 1 and 3) of random type with random stats to participants vector
	int numEnemies = rand() % 3 + 1;
	for (int i = 0; i < numEnemies; i++) {
		participants.push_back(EnemyFactory::getInstance()->makeEnemy());
	}
}

bool Room::getNorth()
{
	return north;
}

bool Room::getSouth()
{
	return south;
}

bool Room::getEast()
{
	return east;
}

bool Room::getWest()
{
	return west;
}

void Room::setRoomX(int x)
{
	room_x = x;
}

int Room::getRoomX()
{
	return room_x;
}

void Room::setRoomY(int y)
{
	room_y = y;
}

int Room::getRoomY()
{
	return room_y;
}

void Room::setNorth(bool boolean)
{
	north = boolean;
}

void Room::setSouth(bool boolean)
{
	south = boolean;
}

void Room::setEast(bool boolean)
{
	east = boolean;
}

void Room::setWest(bool boolean)
{
	west = boolean;
}