// List.cpp - Implementation of List ADT using Array
#include "pch.h"
#include "List.h"  // header file
#include <iostream>
#include <string>

// constructor
List::List() { size = 0; }

// add an item to the back of the list (append)
bool List::add(string s)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = s;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// display the items in the list
void List::print()
{
	for (int i = 0; i < size; i++) //getLenght()
	{
		cout << items[i] << endl;   //get(i)
	}
}

bool List::remove(int index) {
	int i = index - 1;
	bool success = (i >= 0) && (i < size);
	if (success)
	{  // delete item by shifting all items at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = i; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;  // decrease the size by 1
	}
	return success;
}

// get an item at a specified position of the list (retrieve)
string List::get(string n)
{
	bool checker = false;
	string s;
	for (int i = 0; i < size; i++) {
		if (n == items[i]) {
			cout << items[i] << endl;   //get(i)
			s = items[i];
			break;
		}
	}
	return s;
}

