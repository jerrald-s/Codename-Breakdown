// Codename-Breakdown.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "List.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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

list readStation() {
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

int main()
{
	List listInterchange;
	List stationList;
	/*listInterchange = getInterchange();
	stationList = readStation();*/
	menu();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
