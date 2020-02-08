#include "pch.h"
#include "DijkstraAlgorithm.h"


DijkstraAlgorithm::DijkstraAlgorithm()
{
	size = 0;
}


DijkstraAlgorithm::~DijkstraAlgorithm()
{
	DijkstraNode *tempNode;
	for (int i = 0; i < size; i++)
	{
		tempNode = shortestRoute[i];
		delete tempNode;
	}
	//delete shortestRoute;
}

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

DijkstraAlgorithm::DijkstraNode* DijkstraAlgorithm::get(int index)
{
	return shortestRoute[index];
}

int DijkstraAlgorithm::getLength()
{
	return size;
}

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

int DijkstraAlgorithm::update(WeightType newDistance, PathType newPath, int index)
{
	shortestRoute[index]->totalDistance = newDistance;
	shortestRoute[index]->path = newPath;
	return newDistance;
}