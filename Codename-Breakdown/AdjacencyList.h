#pragma once
#include<string>
#include<iostream>
using namespace std;
#include "List.h"
#include "BST.h"
#include "LinkedList.h"

const int MAX_SIZE = 1001;
typedef string LineType;
typedef string CodeType;
typedef string ItemType;
typedef int NextStaType;
typedef int DistType;
typedef string FullCodeType;

class AdjacencyList
{
private:
	struct Node
	{
		NextStaType nextStationIndex;
		DistType distance;
		Node *next;
	};

	struct HeaderNode
	{
		LineType line;
		CodeType stationCode;
		ItemType name;
		Node *next;
	};

	HeaderNode *stations[MAX_SIZE] = { 0 };
	int  size;

public:

	AdjacencyList();

	~AdjacencyList();

	// Add a new station
	bool addStation(LineType line, CodeType stationCode, ItemType name);

	// Add a new interchange station
	bool addIntStation(LineType line, CodeType stationCode, int index);

	// Add adjacent station to a station(adjacency list)
	bool addAdjacentStation(int currentIndex, NextStaType nextStationIndex, DistType distance);

	int getIndex(FullCodeType fullStationCode);

	int getIndex(LineType line, CodeType stationCode);

	void get(int index);

	string getLine(int index);

	int displayLine(LineType line);

	bool displayStationInformation(ItemType name);

	bool addNewStation(ItemType name, LineType line, CodeType stationCode);

	bool displayRouteAndPrice();

	int getSize();

	LinkedList getAllLines();

	int displayNumberOfStation(LineType line);

	bool modifyRoutes(LineType line, int code, int index, int weight1, int weight2);

	List getAllStationNumber(LineType line);
};

