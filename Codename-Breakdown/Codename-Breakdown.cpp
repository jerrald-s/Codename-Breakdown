#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<cctype>
using namespace std;
#include "AdjacencyList.h"
#include "List.h"
#include "LinkedList.h"


void setUpRoute(List stationList, List weightList, AdjacencyList metro) {
	// forward direction
	for (int i = 0; i < weightList.getLength(); i++)
	{
		string currentStation = stationList.get(i);
		int currentStationIndex = metro.getIndex(currentStation);
		string nextStation = stationList.get(i + 1);
		int nextStationIndex = metro.getIndex(nextStation);
		metro.addAdjacentStation(currentStationIndex, nextStationIndex, stoi(weightList.get(i)));
		cout << currentStation << " goes to " << nextStation << " after " << weightList.get(i) << "metres." << endl;
	}

	// other direction
	for (int i = weightList.getLength() - 1; i > 0; i--)
	{
		string currentStation = stationList.get(i);
		int currentStationIndex = metro.getIndex(currentStation);
		string nextStation = stationList.get(i - 1);
		int nextStationIndex = metro.getIndex(nextStation);
		metro.addAdjacentStation(currentStationIndex, nextStationIndex, stoi(weightList.get(i)));
		cout << currentStation << " goes to " << nextStation << " after " << weightList.get(i) << "metres." << endl;
	}
}

List getInterchange() {
	ifstream myFile;
	List interchangeList;
	string stations;
	myFile.open("Interchanges.csv");
	if (myFile.is_open()) {
		while (myFile >> stations) {
			interchangeList.add(stations);
		}
	}
	//interchangeList.print();
	return interchangeList;
}

List readStation() {
	ifstream myFile;
	List stationList;
	string stations;
	string codeandnumber;
	string code;
	string number;
	string name;
	myFile.open("Stations.csv");
	if (myFile.is_open()) {
		while (getline(myFile, stations)) {
			code = "";
			number = "";
			stringstream ss(stations);
			getline(ss, codeandnumber, ',');
			getline(ss, name, ',');
			for (int i = 0; i < codeandnumber.length(); i++) {
				if (isdigit(codeandnumber[i]))
					number.push_back(codeandnumber[i]);
				else if ((codeandnumber[i] >= 'A' && codeandnumber[i] <= 'Z') ||
					(codeandnumber[i] >= 'a' && codeandnumber[i] <= 'z'))
					code.push_back(codeandnumber[i]);
			}
			//cout << code + "," + number + "," + name << endl;
			stationList.add(code + "," + number + "," + name);
		}
	}
	return stationList;
}

void getWeight(AdjacencyList metro) {
	List routes;
	ifstream myFile;
	List stationList;
	List weightList;
	string line;
	string content;
	string source;
	string destination;
	int weight;
	int count = 0;
	myFile.open("Routes.csv");
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			stringstream ss(line);
			while (getline(ss, content, ',')) {
				if (count % 2 == 0) {
					stationList.add(content);
				}
				else {
					weightList.add(content);
				}
			
			}

			if (count % 2 != 0) {
				setUpRoute(stationList, weightList, metro);
				int stationListNo = stationList.getLength();
				int weightListNo = weightList.getLength();
				for (int a = 0; a < stationListNo; a++) {
					stationList.remove(1);
				}
				for (int b = 0; b < weightListNo; b++) {
					weightList.remove(1);
				}
			}
			count++;
		}
	}
}

List getFare() {
	ifstream myFile;
	List fareList;
	string fare;
	myFile.open("Fares.csv");
	if (myFile.is_open()) {
		while (myFile >> fare) {
			fareList.add(fare);
		}
	}
	return fareList;
}

void menu(AdjacencyList metro) {
	bool run = true;
	while (run) {
		cout << "---------------- Main Menu ------------------- \n [1] Display all stations in a given line \n [2] Display station information \n [3] Add and save new station on a given line \n [4] Display route information \n [0] Exit \n---------------------------------------------- \n Enter your option : ";
		int x;
		cin >> x;
		if (x == 1) {
			string line;
			cout << "Which line do you want to see: ";
			cin >> line;
			cout << metro.displayLine(line) << endl;
		}
		if (x == 2) {
			string name;
			cout << "Which station do you want to see: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name);
			metro.displayStationInformation(name);
		}
		if (x == 3) {
			string name;
			string codeandnumber;
			string line;
			string stationCode;
			cout << "Key in station name: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name);
			cout << "Key in line code: ";
			cin >> codeandnumber;
			for (int i = 0; i < codeandnumber.length(); i++) {
				if (isdigit(codeandnumber[i]))
					stationCode.push_back(codeandnumber[i]);
				else if ((codeandnumber[i] >= 'A' && codeandnumber[i] <= 'Z') ||
					(codeandnumber[i] >= 'a' && codeandnumber[i] <= 'z'))
					line.push_back(codeandnumber[i]);
			}
		}
		if (x == 4) {

		}
		if (x == 0) {
			run = false;
		}
	}
}

AdjacencyList setup(List stationList, List interchangeList, AdjacencyList metro)
{
	for (int i = 0; i < stationList.getLength(); i++)
	{
		List tokens;
		stringstream ss(stationList.get(i));
		string intermediate;
		bool checkInterchangeExist = false;
		while (getline(ss, intermediate, ','))
		{
			tokens.add(intermediate);
		}
		string stationCode = tokens.get(0) + tokens.get(1);
		for (int j = 0; j < interchangeList.getLength(); j++)
		{
			List tokens2;
			stringstream ss2(interchangeList.get(j));
			string intermediate2;
			while (getline(ss2, intermediate2, ','))
			{
				tokens2.add(intermediate2);
			}

			bool isInterchange = false;
			for (int k = 0; k < tokens2.getLength(); k++)
			{
				if (stationCode == tokens2.get(k)) {
					isInterchange = true;
					break;
				}
			}
			if (isInterchange)
			{
				for (int l = 0; l < tokens2.getLength(); l++)
				{
					if (stationCode != tokens2.get(l))
					{
						int index = metro.getIndex(tokens2.get(l));
						if (index != -1)
						{
							metro.addIntStation(tokens.get(0), tokens.get(1), index);
							checkInterchangeExist = true;
							//cout << "Interchange " << stationCode << " added" << endl;
							cout << "Setting up..." << endl;
							break;
						}
					}
				}
				if (checkInterchangeExist)
					break;
			}
		}
		if (!checkInterchangeExist)
		{
			metro.addStation(tokens.get(0), tokens.get(1), tokens.get(2));
			//cout << tokens.get(0) + tokens.get(1) << " added" << endl;
		}
	}
	return metro;
}

int main()
{
	List interchangeList = getInterchange();
	List stationList = readStation();
	AdjacencyList metro;
	metro = setup(stationList, interchangeList, metro);
	getWeight(metro);
	LinkedList stationCodeList = metro.getAllLines();

	//uncomment bottom section if u want to verify the stationcode linnked list
	/*cout << metro.getSize() << endl; 
	for (int i = 0; i < metro.getSize(); i++) {
		metro.get(i);
		cout << i << endl;
	}*/

	menu(metro);
}