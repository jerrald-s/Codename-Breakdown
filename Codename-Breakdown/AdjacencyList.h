#pragma once
#include<string>
#include<iostream>
#include "List.h"
#include "BST.h"
#include "DijkstraAlgorithm.h"
#include "Queue.h"
#include "LinkedList.h"
using namespace std;


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
		int visited;
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

	int getIndex(FullCodeType fullStationCode, LinkedList refTable);

	int getIndex(LineType line, CodeType stationCode);

	int getIndexFromName(string name);

	void get(int index);

	int displayLine(LineType line);

	bool displayStationInformation(ItemType name);

	//bool addNewStation(ItemType name, LineType line, CodeType stationCode);

	bool displayRouteAndPrice(int startIndex, int destIndex, AdjacencyList metro, List fare);

	int getSize();

	string retrieveFullStationCode(LineType line, CodeType stationCode);

	LinkedList getAllLines();

	int displayNumberOfStation(LineType line);
};

