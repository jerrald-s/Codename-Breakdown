#include "pch.h"
#include "AdjacencyList.h"
#include <string>
#include <sstream>
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
	headerNode->visited = false;
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

int AdjacencyList::getIndexFromName(string name)
{
	for (int i = 0; i < size; i++)
	{
		if (stations[i]->name == name)
			return i;
		//else
			//cout << stations[i]->name << endl;
	}
	return -1;
}

int AdjacencyList::displayLine(LineType line)
{
	int numberOfLines = 0;
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
					numberOfLines++;
				}
				else
				{
					displayTree.insert(NULL, tokens.get(j), stations[i]->name);
					numberOfLines++;
				}
			}
		}
	}
	displayTree.inorder();
	return numberOfLines;
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

bool AdjacencyList::displayRouteAndPrice(int startIndex, int endIndex, AdjacencyList metro, List fare)
{
	DijkstraAlgorithm shortestPath;
	Queue queue;
	HeaderNode *currentNode;
	Node *tempNode;
	int currentSelected = 0;
	queue.enqueue(startIndex);

	int currentIndex = startIndex;
	
	currentNode = stations[startIndex];
	shortestPath.add(retrieveFullStationCode(stations[currentIndex]->line, stations[currentIndex]->stationCode), 0, queue, true);
	stations[currentIndex]->visited = true;
	while (currentIndex != endIndex)
	{
		tempNode = currentNode->next;
		while (tempNode != NULL)
		{
			if (stations[tempNode->nextStationIndex]->visited == false) {
				string fullStationCode = retrieveFullStationCode(stations[tempNode->nextStationIndex]->line, stations[tempNode->nextStationIndex]
					->stationCode);
				int tempDistance = shortestPath.get(currentSelected)->totalDistance + tempNode->distance;
				int checkExist = shortestPath.checkExist(fullStationCode);
				Queue tempQueue;
				tempQueue = tempQueue.clone(shortestPath.get(currentSelected)->path, tempQueue);
				tempQueue.enqueue(tempNode->nextStationIndex);
				if (checkExist == -1)
				{
					shortestPath.add(fullStationCode, tempDistance, tempQueue, false);
					//cout << "Station " << fullStationCode << " Added!" << endl;
				}
				else
				{
					if (tempDistance < shortestPath.get(checkExist)->totalDistance)
					{
						shortestPath.update(tempDistance, tempQueue, checkExist);
					}
				}
			}
			tempNode = tempNode->next;
		}
		currentSelected = shortestPath.getNextShortest();
		currentIndex = shortestPath.get(currentSelected)->path.getBack();
		currentNode = stations[currentIndex];
		currentNode->visited = true;
	}
	//cout << "Dest: " << currentNode->name << endl;
	List pathIndexList;
	pathIndexList = shortestPath.get(currentSelected)->path.displayItems(pathIndexList);
	for (int j = 0; j < pathIndexList.getLength(); j++)
	{
		cout << retrieveFullStationCode(stations[stoi(pathIndexList.get(j))]->line, stations[stoi(pathIndexList.get(j))]->stationCode) 
			<< " " << stations[stoi(pathIndexList.get(j))]->name << endl;
	}
	cout << "Total Distance: " << shortestPath.get(currentSelected)->totalDistance << endl;

	// Calculate Fare
	double totalFare;
	for (int p = 0; p < fare.getLength(); p++)
	{
		List tokens;
		stringstream ss(fare.get(p));
		string intermediate;
		while (getline(ss, intermediate, ','))
		{
			tokens.add(intermediate);
		}
		if (shortestPath.get(currentSelected)->totalDistance >= stod(tokens.get(0)) * 1000)
		{
			totalFare = stod(tokens.get(1))/100;
		}
	}
	cout << "Metro fare will be $" << totalFare << "." << endl;


	// Reset all visited node's visited to false
	int resetIndex;
	for (int l = 0; l < metro.getSize(); l++)
	{
		stations[l]->visited = false;
	}
	return true;
}

//bool AdjacencyList::addNewStation(ItemType name, LineType line, CodeType stationCode) {
//
//}

void AdjacencyList::get(int index)
{
	cout << stations[index]->name << endl;
}

int AdjacencyList::getSize() {
	return size;
}

string AdjacencyList::retrieveFullStationCode(LineType line, CodeType stationCode)
{
	List tokens;
	stringstream ss(line);
	string intermediate;
	while (getline(ss, intermediate, ','))
	{
		tokens.add(intermediate);
	}
	List tokens2;
	stringstream ss2(stationCode);
	string intermediate2;
	while (getline(ss2, intermediate2, ','))
	{
		tokens2.add(intermediate2);
	}

	string fullStationCode = tokens.get(0) + tokens2.get(0);
	for (int i = 1; i < tokens.getLength(); i++)
	{
		fullStationCode = fullStationCode + "/" + tokens.get(i) + tokens2.get(i);
	}
	return fullStationCode;
}

LinkedList AdjacencyList::getAllLines() {
	LinkedList lineList;
	List codes;
	string line;
	string stationCode;
	HeaderNode *currentNode;
	HeaderNode *currentNode2;
	for (int i = 0; i < size; i++) {
		currentNode = stations[i];
		stringstream ss(currentNode->line);
		while (getline(ss, stationCode, ',')) {
			if (codes.get(stationCode) == "") {
				codes.add(stationCode);
			}
		}
	}
	for (int j = 0; j < codes.getLength(); j++) {
		string currentStationCode = codes.get(j);
		int numberOfStations = displayNumberOfStation(currentStationCode);
		int counter = 0;
		int source = size;
		int final = -1;
		for (int k = 0; k < size; k++) {
			bool checker = false;
			currentNode2 = stations[k];
			stringstream ss(currentNode2->line);
			while (getline(ss, stationCode, ',')) {
				if (stationCode == currentStationCode) {
					checker = true;
					counter++;
					if (source > k) {
						source = k;
					}
					if (final < k) {
						final = k;
					}
					break;
				}
				else {
					continue;
				}
			}
			if (counter == numberOfStations) {
				lineList.add(currentStationCode, source, final);
				break;
			}
		}
	}
	return lineList;
}

int AdjacencyList::displayNumberOfStation(LineType line)
{
	int numberOfLines = 0;
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
					numberOfLines++;
				}
				else
				{
					numberOfLines++;
				}
			}
		}
	}
	return numberOfLines;
}
