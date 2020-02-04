// List.h - - Specification of List ADT
#pragma once
#include <iostream>
#include <string>
using namespace std;

const int LIST_MAX_SIZE = 1000;

class List
{
private:
	string items[LIST_MAX_SIZE];
	int size;

public:

	// constructor
	List();

	void print();
	bool add(string);
	bool remove(int);
	string get(string);
	string get(int);
	int getLength();
};



