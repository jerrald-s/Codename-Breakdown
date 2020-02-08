#include "pch.h"
#include "AdjacencyList.h"
#include <string>
#include "List.h"
#include <sstream>
#include "BST.h"
#include <iostream>
#include <fstream>
#include "LinkedList.h"


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

bool AdjacencyList::displayRouteAndPrice()
{
	return true;
}

//bool AdjacencyList::addNewStation(ItemType name, LineType line, CodeType stationCode) {
//
//}

void AdjacencyList::get(int index)
{
	cout << stations[index]->name << endl;
	cout << stations[index]->line << endl;
	cout << stations[index]->stationCode << endl;
}

string AdjacencyList::getLine(int index)
{
	return stations[index]->line;
}

int AdjacencyList::getSize() {
	return size;
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

List AdjacencyList::getAllStationNumber(LineType line) {
	List numberList;
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
					numberList.add(tokens2.get(j));
				}
				//specially for full station codes without number
				else
				{
					numberList.add("-1");
				}
			}
		}
	}
	return numberList;

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

bool AdjacencyList::modifyRoutes(LineType line, int code, int index, int weight1, int weight2) {
	HeaderNode *currentNode;
	int counter = 0;
	int biggestNum = -1;
	int frontNumber = -2;
	int backNumber = -2;
	int frontIndex = -1;
	int backIndex;
	string lineCode;
	string line;
	string stationNum;
	string stationNum2;
	List numberList = getAllStationNumber(line);
	int numberOfStations = displayNumberOfStation(line);
	for (int i = 0; i < size; i++) {
		currentNode = stations[i];
		bool checker = false;
		stringstream ss1(currentNode->line);
		stringstream ss2(currentNode->stationCode);
		while (getline(ss1, lineCode, ',')) {
			(getline(ss2, stationNum, ','));
			if (lineCode == line) {
				counter++;
				int stationNumInt;
				stringstream stationNumSS(stationNum);
				stationNumSS >> stationNumInt;
				if (stationNumInt > frontNumber && stationNumInt < code) {
					frontNumber = stationNumInt;
					frontIndex = i;
				}
			}
			else {
				continue;
			}
		}
	}
	//getting back index and back number
	for (int j = 0; j = numberList.getLength(); j++) {
		int numberRecordInt;
		stringstream numberRecord(numberList.get(j));
		numberRecord >> numberRecordInt;
		if (backNumber < numberRecordInt) {
			backNumber = numberRecordInt;
		}
		else {
			continue;
		}
	}
	//get the next bigger number of the inserted station number
	for (int k = 0; k = numberList.getLength(); k++) {
		int numberRecordInt;
		stationNum2 = numberList.get(k);
		stringstream numberRecord(stationNum2);
		numberRecord >> numberRecordInt;
		if (numberRecordInt > code && numberRecordInt <= backNumber) {
			backNumber = numberRecordInt;
		}
		else {
			continue;
		}
	}
	string fullBackStationCode = line + stationNum2;
	backIndex = getIndex(fullBackStationCode);
	if (frontNumber != -2) {
		addAdjacentStation(index, frontIndex, weight1);
	}
	if (backNumber != -2) {
		addAdjacentStation(index, backIndex, weight2);
	}
}
