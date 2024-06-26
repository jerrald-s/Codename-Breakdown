#pragma once
#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string LinkedListItemType;

class LinkedList
{
private:
	struct LinkedListNode
	{
		LinkedListItemType item;	// item
		int				   startPosition;
		int				   endPosition;
		LinkedListNode    *next;	// pointer pointing to next item
	};
	LinkedListNode *firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	LinkedList();

	// destructor
	/*~List();*/

	// add an item to the back of the list (append)
	bool add(LinkedListItemType item, int startPosition, int endPosition);

	// add an item at a specified position in the list (insert)
	bool add(int index, LinkedListItemType item, int startPosition, int endPosition);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	LinkedListItemType get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void print();

	bool update(int index, int endPosition);

	bool updateInt(int index, int startPosition, int endPosition);

	int getStartPosition(int index);

	int getStartPosition(LinkedListItemType code);

	int getEndPosition(int index);

	int getEndPosition(LinkedListItemType code);
};

