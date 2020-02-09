#include "pch.h"
#include "AdjacencyList.h"
#include <cctype>
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

int AdjacencyList::getIndex(FullCodeType fullStationCode, LinkedList refTable)
{
	HeaderNode *currentNode;
	string line;
	for (int p = 0; p < fullStationCode.length(); p++)
	{
		if ((fullStationCode[p] >= 'A' && fullStationCode[p] <= 'Z') ||
			(fullStationCode[p] >= 'a' && fullStationCode[p] <= 'z'))
		{
			line.push_back(fullStationCode[p]);
		}
	}

	int startIndex = refTable.getStartPosition(line);
	int endIndex = refTable.getEndPosition(line);

	for (int i = startIndex; i < (endIndex + 1); i++)
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

string AdjacencyList::getCodes(int index)
{
	return stations[index]->stationCode;
}

string AdjacencyList::getLine(int index)
{
	return stations[index]->line;
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
				if (tokens2.get(j) != "") {
					StaCodeType stationCode = stoi(tokens2.get(j));
					numberList.add(tokens2.get(j));
				}
				//specially for full station codes without number
				else
				{
					numberList.add("0");
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

bool AdjacencyList::modifyRoutes(LineType line, int code, int index) {
	HeaderNode *currentNode;
	int counter = 0;
	int biggestNum = -1;
	int frontNumber = -2;
	int backNumber = -2;
	int frontIndex = -1;
	int backIndex = -1;
	string lineCode;
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
				if (stationNumInt > backNumber && stationNumInt < code) {
					backNumber = stationNumInt;
					backIndex = i;
				}
			}
			else {
				continue;
			}
		}
	}
	//getting front index and front number
	for (int j = 0; j < numberList.getLength(); j++) {
		int numberRecordInt;
		stringstream numberRecord(numberList.get(j));
		numberRecord >> numberRecordInt;
		if (frontNumber < numberRecordInt) {
			frontNumber = numberRecordInt;
		}
		else {
			continue;
		}
	}
	//get the next bigger number of the inserted station number
	for (int k = 0; k < numberList.getLength(); k++) {
		int numberRecordInt;
		stationNum2 = numberList.get(k);
		stringstream numberRecord(stationNum2);
		numberRecord >> numberRecordInt;
		if (numberRecordInt > code && numberRecordInt <= frontNumber) {
			frontNumber = numberRecordInt;
			string fullBackStationCode = line + stationNum2;
			frontIndex = getIndex(fullBackStationCode);
		}
		else {
			continue;
		}
	}
	if (backIndex != -1) {
		string backWeight;
		int backWeightInt;
		while (true) {
			bool intchecker = true;
			cout << "Enter the route distance between the newly added station and the station behind it:";
			cin >> backWeight;
			for (int l = 0; l < backWeight.size(); l++) {
				if (isdigit(backWeight[l])) {
					continue;
				}
				else {
					intchecker = false;
					break;
				}
			}
			if (intchecker == true) {
				stringstream ssback(backWeight);
				ssback >> backWeightInt;
				addAdjacentStation(index, backIndex, backWeightInt);
				updateAdjacentStation(backIndex, frontIndex, index, backWeightInt);
				break;
			}
			else {
				cout << "Route distance can only be in integers" << endl;
			}
		}
	}
	if (frontIndex != -1) {
		string frontWeight;
		int frontWeightInt;
		while(true) {
			bool intchecker = true;
			cout << "Enter the route distance between the newly added station and the station in front of it:";
			cin >> frontWeight;
			for (int l = 0; l < frontWeight.size(); l++) {
				if (isdigit(frontWeight[l])) {
					continue;
				}
				else {
					intchecker = false;
					break;
				}
			}
			if (intchecker == true) {
				stringstream ssfront(frontWeight);
				ssfront >> frontWeightInt;
				addAdjacentStation(index, frontIndex,frontWeightInt);
				updateAdjacentStation(frontIndex, backIndex, index, frontWeightInt);
				break;
			}
			else {
				cout << "Route distance can only be in integers" << endl;
			}
		}
	}
	return true;
}

bool AdjacencyList::updateAdjacentStation(int currentIndex, NextStaType oldIndex , NextStaType nextStationIndex, DistType distance) {
	HeaderNode *currentHeaderNode;
	Node *currentNode;
	currentHeaderNode = stations[currentIndex];
	if (currentHeaderNode->next != nullptr) {
		currentNode = currentHeaderNode->next;
		if (oldIndex != -1) {
			while (currentNode->nextStationIndex != oldIndex && currentNode->next != nullptr) {
				currentNode = currentNode->next;
			}
		}
		if (currentNode->nextStationIndex == oldIndex) {
			currentNode->nextStationIndex = nextStationIndex;
			currentNode->distance = distance;
		}
		else {
			addAdjacentStation(currentIndex, nextStationIndex, distance);
		}
	}
	else {
		if (oldIndex == -1) {
			oldIndex = currentIndex;
			addAdjacentStation(oldIndex, nextStationIndex, distance);
		}
	}
	return true;
}

void AdjacencyList::saveStation(AdjacencyList metro, LinkedList refTable) {
	ofstream myFile;
	string line;
	myFile.open("NewStations.csv");
	for (int i = 0; i < refTable.getLength(); i++)
	{
		int countNextStation = 0;
		int numOfStationCounted = 0;
		int frontNumber = 99999;
		line = refTable.get(i);
		List numberList = getAllStationNumber(line);
		cout << "Saving Stations.csv for line: " << line << endl;
		//getting front number
		for (int j = 0; j < numberList.getLength(); j++) {
			int numberRecordInt;
			stringstream numberRecord(numberList.get(j));
			numberRecord >> numberRecordInt;
			if (numberRecordInt < frontNumber) {
				frontNumber = numberRecordInt;
			}
			else {
				continue;
			}
		}
		int numberOfStation = metro.displayNumberOfStation(line);
		while (numOfStationCounted != numberOfStation) {
			int k = 0;
			for (k; k < metro.getSize(); k++) {
				bool added = false;
				string writeLine = "";
				// Put HeaderNode line and StationCode into Vector(Array) in case it is an interchange
				List tokens;
				stringstream ss(stations[k]->line);
				string intermediate;
				while (getline(ss, intermediate, ','))
				{
					tokens.add(intermediate);
				}
				List tokens2;
				string stringinter2 = stations[k]->stationCode;
				int stringinter2count = stringinter2.length();
				stringstream ss2(stations[k]->stationCode);
				string intermediate2;
				while (getline(ss2, intermediate2, ','))
				{
					tokens2.add(intermediate2);
				}
				if (stringinter2.at(stringinter2count - 1) == ',') {
					tokens2.add("0");
				}
				// Check whether station exist
				for (int l = 0; l < tokens.getLength(); l++)
				{
					if (tokens.get(l) == line)
					{
						int stationNum;
						stringstream ssStationNum(tokens2.get(l));
						ssStationNum >> stationNum;
						if (stationNum != frontNumber) {
							continue;
						}
						//else if (stationNum)
						else {
							//cout << stations[k]->name << endl;
							if (tokens.getLength() == tokens2.getLength()) {
								if (tokens2.get(l) == "0") {
									writeLine = tokens.get(l) +  "," + stations[k]->name + "\n";
								}
								else {
									writeLine = tokens.get(l) + tokens2.get(l) + "," + stations[k]->name + "\n";
								}
								myFile << writeLine;
								frontNumber++;
								numOfStationCounted++;
								added = true;
							}
							//specially for full station codes without number
							else
							{
								writeLine = tokens.get(l) + "," + stations[k]->name + "\n";
								myFile << writeLine;
								frontNumber++;
								numOfStationCounted++;
								added = true;
							}
						}
					}
				}
				if(added == true){
					break;
				}
				if (k + 1 == metro.getSize()) {
					frontNumber++;
					break;
				}
			}
		}
	}
}

void AdjacencyList::saveRoutes(AdjacencyList metro, LinkedList refTable) {
	ofstream myFile;
	string line;
	myFile.open("NewRoutes.csv");
	for (int i = 0; i < refTable.getLength(); i++)
	{
		int countNextStation = 0;
		int numOfStationCounted = 0;
		int frontNumber = 99999;
		string writeStationLine = "";
		string writeRouteLine = "";
		line = refTable.get(i);
		List numberList = getAllStationNumber(line);
		cout << "Saving Routes.csv for line: " << line << endl;
		//getting front number
		for (int j = 0; j < numberList.getLength(); j++) {
			int numberRecordInt;
			stringstream numberRecord(numberList.get(j));
			numberRecord >> numberRecordInt;
			if (numberRecordInt < frontNumber) {
				frontNumber = numberRecordInt;
			}
			else {
				continue;
			}
		}
		int numberOfStation = metro.displayNumberOfStation(line);
		while (numOfStationCounted != numberOfStation) {
			int k = 0;
			for (k; k < metro.getSize(); k++) {
				int hehe = metro.getSize();
				bool added = false;
				string writeLine = "";
				// Put HeaderNode line and StationCode into Vector(Array) in case it is an interchange
				List tokens;
				stringstream ss(stations[k]->line);
				string intermediate;
				while (getline(ss, intermediate, ','))
				{
					tokens.add(intermediate);
				}
				List tokens2;
				string stringinter2 = stations[k]->stationCode;
				int stringinter2count = stringinter2.length();
				stringstream ss2(stations[k]->stationCode);
				string intermediate2;
				while (getline(ss2, intermediate2, ','))
				{
					tokens2.add(intermediate2);
				}
				if (stringinter2.at(stringinter2count - 1) == ',') {
					tokens2.add("0");
				}
				// Check whether station exist
				for (int l = 0; l < tokens.getLength(); l++)
				{
					if (tokens.get(l) == line)
					{
						int stationNum;
						stringstream ssStationNum(tokens2.get(l));
						ssStationNum >> stationNum;
						if (stationNum != frontNumber) {
							continue;
						}
						//adding process if the correct order of the specific station number matches the supposed order
						else {
							HeaderNode *currentHeaderNode;
							Node *currentNode;
							currentHeaderNode = stations[k];
							//for headernodes without nodes
							if (currentHeaderNode->next == nullptr) {
								writeStationLine = writeStationLine + line + to_string(stationNum);
								frontNumber++;
								numOfStationCounted++;
								added = true;
								break;
							}
							//for headernodes with only one node inside
							else if (currentHeaderNode->next->next == nullptr) {
								writeStationLine = writeStationLine + line + to_string(stationNum) + ",";
								writeRouteLine = writeRouteLine + to_string(currentHeaderNode->next->distance) + ",";
								frontNumber++;
								numOfStationCounted++;
								added = true;
								break;
							}
							//for headernodes with more than one node inside
							else {
								currentNode = currentHeaderNode->next;
								while (currentNode->next != nullptr) {
									//List headerToken;
									string innercodes;
									List innerLinesList;
									List innerCodesList;
									int ssheaderToken(currentNode->nextStationIndex);
									string innerLineString;
									stringstream innerLines(getLine(ssheaderToken));
									while (getline(innerLines, innerLineString, ',')) {
										innerLinesList.add(innerLineString);
									}
									string innerCodeString;
									stringstream innerCodes(getCodes(ssheaderToken));
									while (getline(innerCodes, innerCodeString, ',')) {
										innerCodesList.add(innerCodeString);
									}
									for (int m = 0; m < innerLinesList.getLength(); m++) {
										if (innerLinesList.get(l) == line) {
											int innerCodeInt;
											stringstream ssInnerCode(innerCodesList.get(m));
											ssInnerCode >> innerCodeInt;
											if (stationNum < innerCodeInt) {
												writeStationLine = writeStationLine + line + to_string(stationNum) + ",";
												writeRouteLine = writeRouteLine + to_string(currentNode->distance) + ",";
												frontNumber++;
												numOfStationCounted++;
												added = true;
												break;
											}
										}
										else {
											continue;
										}
									}
									currentNode = currentNode->next;
								}
								//for the last node base on the above func
								if (added == false) {
									//List headerToken;
									string innercodes;
									List innerLinesList;
									List innerCodesList;
									int ssheaderToken(currentNode->nextStationIndex);
									string innerLineString;
									stringstream innerLines(getLine(ssheaderToken));
									while (getline(innerLines, innerLineString, ',')) {
										innerLinesList.add(innerLineString);
									}
									string innerCodeString;
									stringstream innerCodes(getCodes(ssheaderToken));
									while (getline(innerCodes, innerCodeString, ',')) {
										innerCodesList.add(innerCodeString);
									}
									for (int m = 0; m < innerLinesList.getLength(); m++) {
										if (innerLinesList.get(l) == line) {
											int innerCodeInt;
											stringstream ssInnerCode(innerCodesList.get(m));
											ssInnerCode >> innerCodeInt;
											if (stationNum < innerCodeInt) {
												writeStationLine = writeStationLine + line + to_string(stationNum) + ",";
												writeRouteLine = writeRouteLine + to_string(currentNode->distance) + ",";
												frontNumber++;
												numOfStationCounted++;
												added = true;
												break;
											}
										}
										else {
											continue;
										}
									}
								}
							}
						}
					}
				}
				if (added == true) {
					break;
				}
				if (k + 1 == metro.getSize()) {
					frontNumber++;
					break;
				}
			}
			if (numOfStationCounted == numberOfStation) {
				writeStationLine.pop_back();
				writeRouteLine.pop_back();
				myFile << writeStationLine + "\n";
				myFile << writeRouteLine + "\n";
				break;
			}
		}
	}
}
