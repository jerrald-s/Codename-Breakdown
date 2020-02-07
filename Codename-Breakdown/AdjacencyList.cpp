#include "pch.h"
#include "AdjacencyList.h"
#include <string>
#include "List.h"
#include <sstream>
#include "BST.h"
#include <iostream>
#include <fstream>


AdjacencyList::AdjacencyList()
{
	size = 0;
}


AdjacencyList::~AdjacencyList()
{
}

bool AdjacencyList::addStation(LineType line, CodeType stationCode, ItemType name)
{
	HeaderNode *headerNode = new HeaderNode;
	headerNode->line = line;
	headerNode->stationCode = stationCode;
	headerNode->name = name;
	headerNode->next = NULL;
	stations[size] = headerNode;
	size++;
	return true;
}

bool AdjacencyList::addIntStation(LineType line, CodeType stationCode, int index)
{
	HeaderNode *currentNode;
	currentNode = stations[index];
	currentNode->line = currentNode->line + "," + line;
	currentNode->stationCode = currentNode->stationCode + "," + stationCode;
	return true;
}

bool AdjacencyList::addAdjacentStation(int currentIndex, NextStaType nextStationIndex, DistType distance)
{
	HeaderNode *currentStation = stations[currentIndex];
	Node *newNode = new Node;
	newNode->distance = distance;
	newNode->nextStationIndex = nextStationIndex;
	newNode->next = NULL;
	// currentStation does not have adjacent stations yet
	if (currentStation->next == NULL)
	{
		currentStation->next = newNode;
	}
	// currentStation has adjacent stations
	else
	{
		Node *currentNode = currentStation->next;
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
	}
	return true;
}

int AdjacencyList::getIndex(FullCodeType fullStationCode)
{
	HeaderNode *currentNode;
	for (int i = 0; i < size; i++)
	{
		currentNode = stations[i];

		// Put HeaderNode line and StationCode into Vector(Array) in case it is an interchange
		List tokens;
		stringstream ss(currentNode->line);
		string intermediate;
		while (getline(ss, intermediate, ','))
		{
			tokens.add(intermediate);
		}
		List tokens2;
		stringstream ss2(currentNode->stationCode);
		string intermediate2;
		while (getline(ss2, intermediate2, ','))
		{
			tokens2.add(intermediate2);
		}

		// Check whether station exist
		for (int j = 0; j < tokens.getLength(); j++)
		{
			string stationCode = tokens.get(j) + tokens2.get(j);
			if (stationCode == fullStationCode)
			{
				return i;
			}
		}
	}
	return -1;
}

// Getting of station index using Line+Code, not Station Name.
int AdjacencyList::getIndex(LineType line, CodeType stationCode)
{
	HeaderNode *currentNode;
	for (int i = 0; i < size; i++)
	{
		currentNode = stations[i];

		// Put HeaderNode line and StationCode into Vector(Array) in case it is an interchange
		List tokens;
		stringstream ss(currentNode->line);
		string intermediate;
		while (getline(ss, intermediate, ','))
		{
			tokens.add(intermediate);
		}
		List tokens2;
		stringstream ss2(currentNode->stationCode);
		string intermediate2;
		while (getline(ss2, intermediate2, ','))
		{
			tokens2.add(intermediate2);
		}

		// Check whether station exist
		for (int j = 0; j < tokens.getLength(); j++)
		{
			if (tokens.get(j) == line && tokens2.get(j) == stationCode)
			{
				return i;
			}
		}
	}
	return -1;
}

int AdjacencyList::displayLine(LineType line)
{
	BST displayTree;
	for (int i = 0; i < size; i++)
	{
		// Put HeaderNode line and StationCode into Vector(Array) in case it is an interchange
		List tokens;
		stringstream ss(stations[i]->line);
		string intermediate;
		while (getline(ss, intermediate, ','))
		{
			tokens.add(intermediate);
		}
		List tokens2;
		stringstream ss2(stations[i]->stationCode);
		string intermediate2;
		while (getline(ss2, intermediate2, ','))
		{
			tokens2.add(intermediate2);
		}
		// Check whether station exist
		for (int j = 0; j < tokens.getLength(); j++)
		{
			if (tokens.get(j) == line)
			{
				//cout << stations[i]->name << endl;
				if (tokens.getLength() == tokens2.getLength()) {
					StaCodeType stationCode = stoi(tokens2.get(j));
					displayTree.insert(stoi(tokens2.get(j)), tokens.get(j), stations[i]->name);
				}
				else
				{
					displayTree.insert(NULL, tokens.get(j), stations[i]->name);
				}
			}
		}
	}
	displayTree.inorder();
	return 1;
}

bool AdjacencyList::displayStationInformation(ItemType name)
{
	bool check = false;
	int interchangeChecker = 0;
	string station;
	string code;
	HeaderNode *currentNode;
	for (int i = 0; i < size; i++) {
		currentNode = stations[i];
		if (name == currentNode->name) {
			cout << "Station found!" << endl;
			stringstream ss1(currentNode->line);
			stringstream ss2(currentNode->stationCode);
			cout << "Station code: " << endl;
			while (getline(ss1, station, ',')) {
				(getline(ss2, code, ','));
				cout << station << code << endl;
				interchangeChecker++;
			}
			check = true;
		}
		else {
			continue;
		}
	}
	if (check == false) {
		cout << "Station entered couldn't be found..." << endl;
		return check;
	}
	else {
		if (interchangeChecker == 1) {
			cout << "Station entered is not an interchange." << endl;
		}
		else {
			cout << "Station entered is an interchange." << endl;
		}
		return check;
	}
}

bool AdjacencyList::displayRouteAndPrice()
{
	return true;
}

void AdjacencyList::get(int index)
{
	cout << stations[index]->name << endl;
	cout << stations[index]->line << endl;
	cout << stations[index]->stationCode << endl;
}
