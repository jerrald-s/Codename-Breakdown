// List.h - - Specification of List ADT
#pragma once
#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

class List
{
private:
	string items[MAX_SIZE];
	int size;

public:

	// constructor
	List();

	void print();
	bool add(string);
	bool remove(int);
	string get(string);
};



