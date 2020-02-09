#include "pch.h"
#include "DijkstraAlgorithm.h"

// Constructor
DijkstraAlgorithm::DijkstraAlgorithm()
{
	size = 0;
}

// Destructor
DijkstraAlgorithm::~DijkstraAlgorithm()
{
	DijkstraNode *tempNode;
	for (int i = 0; i < size; i++)
	{
		tempNode = shortestRoute[i];
		delete tempNode;
	}
}

// Adds a new station into the Dijkstra Algorithm
// and returns the totalDistance
int DijkstraAlgorithm::add(FullStationCodeType fullStationCode, WeightType totalDistance, PathType path, ShortestType isShortest)
{
	DijkstraNode *tempNode = new DijkstraNode;
	tempNode->fullStationCode = fullStationCode;
	tempNode->totalDistance = totalDistance;
	tempNode->path = path;
	tempNode->isShortest = isShortest;
	shortestRoute[size] = tempNode;
	size++;
	return totalDistance;
}

// returns a pointer to the DijkstraNode given the index of the Node
DijkstraAlgorithm::DijkstraNode* DijkstraAlgorithm::get(int index)
{
	return shortestRoute[index];
}

// returns the size of the Array
int DijkstraAlgorithm::getLength()
{
	return size;
}

// Search for the next shortest totalDistance station in the Dijkstra Algorithm
// that has not been selected yet
// returns the index of the selected next shortest totalDistance station
int DijkstraAlgorithm::getNextShortest()
{
	int nextShortest;
	int shortestDistance = 999999999;
	for (int i = 0; i < size; i++)
	{
		if (shortestRoute[i]->isShortest == false && shortestRoute[i]->totalDistance < shortestDistance)
		{
			nextShortest = i;
			shortestDistance = shortestRoute[i]->totalDistance;
		}
	}
	shortestRoute[nextShortest]->isShortest = true;
	return nextShortest;
}

// checks whether the station exist in the Dijkstra Algorithm
// and returns the index if it exist, else returns -1
int DijkstraAlgorithm::checkExist(FullStationCodeType fullStationCode)
{
	for (int i = 0; i < size; i++)
	{
		if (shortestRoute[i]->fullStationCode == fullStationCode)
		{
			return i;
		}
	}
	return -1;
}

// Updates the DijkstraNode with the new totalDistance and new path(Queue) given the index
// of the node to be updated
// Returns the new totalDistance
int DijkstraAlgorithm::update(WeightType newDistance, PathType newPath, int index)
{
	shortestRoute[index]->totalDistance = newDistance;
	shortestRoute[index]->path = newPath;
	return newDistance;
}