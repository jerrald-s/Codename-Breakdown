#include "pch.h"
#include "Queue.h"

// Constructor
Queue::Queue()
{
}

// Destructor
Queue::~Queue()
{
}

// Adds item into the Queue
bool Queue::enqueue(QueueItemType item)
{
	QueueNode *tempNode = new QueueNode;
	tempNode->stationIndex = item;
	tempNode->next = NULL;

	if (isEmpty())
	{
		frontNode = tempNode;
	}
	else
	{
		backNode->next = tempNode;
	}
	backNode = tempNode;
	return true;
}

// Removes item from the Queue
bool Queue::dequeue()
{
	QueueNode *removedNode;
	removedNode = frontNode;
	if (frontNode == backNode)
	{
		frontNode = NULL;
		backNode = NULL;
	}
	else
	{
		frontNode = frontNode->next;
	}
	removedNode->next = NULL;
	delete(removedNode);
	return true;
}

// Removes item from the queue and temporary store it in item
bool Queue::dequeue(QueueItemType &item)
{
	QueueNode *removedNode;
	removedNode = frontNode;
	item = removedNode->stationIndex;
	cout << "Removed item is " << item << endl;
	if (frontNode == backNode)
	{
		frontNode = NULL;
		backNode = NULL;
	}
	else
	{
		frontNode = frontNode->next;
	}
	removedNode->next = NULL;
	delete(removedNode);
	return true;
}

// gets the index of the frontNode
void Queue::getFront(QueueItemType &item)
{
	if (!isEmpty())
	{
		item = frontNode->stationIndex;
	}
}

// returns true if the Queue is empty
// else returns false
bool Queue::isEmpty()
{
	if (frontNode == NULL)
	{
		return true;
	}
	return false;
}

// Stores all the stationIndex in the list from the Queue
List Queue::displayItems(List list)
{
	QueueNode *tempNode;
	tempNode = frontNode;
	while (tempNode != NULL)
	{
		list.add(to_string(tempNode->stationIndex));
		tempNode = tempNode->next;
	}
	return list;
}

// returns the backNode stationIndex
QueueItemType Queue::getBack()
{
	return backNode->stationIndex;
}

// returns the length of the Queue
int Queue::getLength()
{
	int count = 0;
	QueueNode *tempNode;
	tempNode = frontNode;
	while (tempNode != NULL)
	{
		count++;
		tempNode = tempNode->next;
	}
	return count;
}

// returns the stationIndex of the node in a given index position
QueueItemType Queue::get(int index)
{
	int count = 0;
	QueueNode *tempNode;
	tempNode = frontNode;
	while (count != index)
	{
		count++;
		tempNode = tempNode->next;
	}
	return tempNode->stationIndex;
}

// duplicate the queue into another queue
// and return the duplicated queue
Queue Queue::clone(Queue original, Queue newQueue)
{
	for (int i = 0; i < original.getLength(); i++)
	{
		newQueue.enqueue(original.get(i));
	}
	return newQueue;
}