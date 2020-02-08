#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Queue.h"
#include "AdjacencyList.h"

const int MAX_SIZE_2 = 1001;
typedef string FullStationCodeType;
typedef int WeightType;
typedef Queue PathType;
typedef bool ShortestType;

class DijkstraAlgorithm
{
private:
	struct DijkstraNode {
		FullStationCodeType fullStationCode;
		WeightType totalDistance;
		PathType path;
		ShortestType isShortest;
	};

	DijkstraNode *shortestRoute[MAX_SIZE_2] = { 0 };
	int size;

public:
	DijkstraAlgorithm();
	~DijkstraAlgorithm();
	int add(FullStationCodeType fullStationCode, WeightType totalDistance, PathType path, ShortestType isShortest);
	DijkstraNode* get(int index);
	int getLength();
	int getNextShortest();
	int checkExist(FullStationCodeType fullStationCode);
	int update(WeightType newDistance, PathType newPath, int index);
};

