#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#include "AdjacencyList.h"
#include "List.h"


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
	interchangeList.print();
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
			cout << code + "," + number + "," + name << endl;
			stationList.add(code + "," + number + "," + name);
		}
	}
	return stationList;
}

void getWeight() {

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

void menu() {
	bool run = true;
	while (run) {
		cout << "---------------- Main Menu ------------------- \n [1] Display all stations in a given line \n [2] Display station information \n [3] Add and save new station on a given line \n [4] Display route information \n [0] Exit \n---------------------------------------------- \n Enter your option : ";
		int x;
		cin >> x;
		if (x == 1) {

		}
		if (x == 2) {

		}
		if (x == 3) {

		}
		if (x == 4) {

		}
		if (x == 0) {
			run = false;
		}
	}
}

void setup(List stationList, List interchangeList)
{
	AdjacencyList metro;
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
			if (interchangeList.get(j).find(stationCode) != std::string::npos) {
				List tokens2;
				stringstream ss2(interchangeList.get(j));
				string intermediate2;
				while (getline(ss2, intermediate2, ','))
				{
					tokens2.add(intermediate2);
				}

				for (int l = 0; l < tokens2.getLength(); l++)
				{
					if (stationCode != tokens2.get(l))
					{
						int index = metro.getIndex(tokens2.get(l));
						if (index != -1)
						{
							metro.get(index);
							metro.addIntStation(tokens.get(0), tokens.get(1), index);
							checkInterchangeExist = true;
							cout << stationCode << " added" << endl;
							metro.get(index);
						}
					}
				}
			}
		}
		if (!checkInterchangeExist)
		{
			metro.addStation(tokens.get(0), tokens.get(1), tokens.get(2));
			cout << tokens.get(0) + tokens.get(1) << " added" << endl;
		}
	}
}

int main()
{
	List interchangeList = getInterchange();
	List stationList = readStation();
	setup(stationList, interchangeList);
	menu();
}