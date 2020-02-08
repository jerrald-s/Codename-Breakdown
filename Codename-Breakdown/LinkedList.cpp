#include "pch.h"
#include "LinkedList.h"
#include<string>
#include<iostream>
using namespace std;

typedef string LinkedListItemType;

LinkedList::LinkedList() { size = 0; }

bool LinkedList::add(LinkedListItemType item, int startPosition, int endPosition) {
	LinkedListNode* newnode = new LinkedListNode;
	newnode->item = item;
	newnode->startPosition = startPosition;
	newnode->endPosition = endPosition;
	newnode->next = NULL;
	LinkedListNode* current = new LinkedListNode;
	current = firstNode;
	if (size == 0) {
		firstNode = newnode;
		size++;
		return true;
	}

	else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newnode;
		size++;
		return true;
	}
}

bool LinkedList::add(int i, LinkedListItemType item, int startPosition, int endPosition) {
	LinkedListNode* newnode = new LinkedListNode;
	newnode->item = item;
	newnode->next = NULL;
	LinkedListNode* current = new LinkedListNode;
	current = firstNode;
	if (i == 0) {
		newnode->next = firstNode;
		firstNode = newnode;
		size++;
		return true;
	}
	else if (i > 0 && i <= size) {
		for (i; i != 1; i--) {
			current = current->next;
		}
		newnode->next = current->next;
		current->next = newnode;
		size++;
		return true;

	}
	else {
		return false;
	}
}

void LinkedList::remove(int i) {
	LinkedListNode* nextnode = new LinkedListNode;
	LinkedListNode* current = new LinkedListNode;
	current = firstNode;
	if (i == 0) {
		/*nextnode = current->next;*/
		firstNode = current->next;
		current->next = NULL;
		delete current;
	}
	else {
		int i2;
		for (i2 = 0; i2 < i - 1; i2++) {
			current = current->next; //current pts to (i-1) position node
		}
		nextnode = current->next; //i position node
		current->next = nextnode->next; //set i+1 position node
		nextnode->next = NULL;
		delete nextnode;
	}
	size--;
}

LinkedListItemType LinkedList::get(int i) {
	LinkedListNode* current = new LinkedListNode;
	current = firstNode;
	for (i; i != 0; i--) {
		current = current->next;
	}
	return current->item;
}

bool LinkedList::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

int LinkedList::getLength() {
	return size;
}

void LinkedList::print() {
	LinkedListNode* current = new LinkedListNode;
	current = firstNode;
	int i;
	for (i = 0; i != size; i++) {
		if (i != size - 1) {
			cout << current->item << ',' << current->startPosition << ',' << current->endPosition << endl;
			current = current->next;
		}
		else {
			cout << current->item << ',' << current->startPosition << ',' << current->endPosition << endl;
			current = current->next;
		}
	}
	//cout << endl;
}

bool LinkedList::update(int index, int endPosition)
{
	int count = 0;
	LinkedListNode *tempNode = firstNode;
	while (count != index)
	{
		tempNode = tempNode->next;
		count++;
	}
	tempNode->endPosition = endPosition;
	return true;
}

bool LinkedList::updateInt(int index, int startPosition, int endPosition)
{
	int count = 0;
	LinkedListNode *tempNode = firstNode;
	while (count != index)
	{
		tempNode = tempNode->next;
		count++;
	}
	tempNode->endPosition = endPosition;
	tempNode->startPosition = startPosition;
	return true;
}

int LinkedList::getStartPosition(int index)
{
	int count = 0;
	LinkedListNode *tempNode = firstNode;
	while (count != index)
	{
		tempNode = tempNode->next;
		count++;
	}
	return tempNode->startPosition;
}

int LinkedList::getStartPosition(LinkedListItemType code)
{
	LinkedListNode *tempNode = firstNode;
	while (tempNode != NULL)
	{
		if (tempNode->item == code)
			return tempNode->startPosition;
		tempNode = tempNode->next;
	}
	return -1;
}

int LinkedList::getEndPosition(int index)
{
	int count = 0;
	LinkedListNode *tempNode = firstNode;
	while (count != index)
	{
		tempNode = tempNode->next;
		count++;
	}
	return tempNode->endPosition;
}

int LinkedList::getEndPosition(LinkedListItemType code)
{
	LinkedListNode *tempNode = firstNode;
	while (tempNode != NULL)
	{
		if (tempNode->item == code)
			return tempNode->endPosition;
		tempNode = tempNode->next;
	}
	return -1;
}
