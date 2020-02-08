#include "pch.h"
#include "Queue.h"


Queue::Queue()
{
}


Queue::~Queue()
{
}

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

void Queue::getFront(QueueItemType &item)
{
	if (!isEmpty())
	{
		item = frontNode->stationIndex;
	}
}

bool Queue::isEmpty()
{
	if (frontNode == NULL)
	{
		return true;
	}
	return false;
}

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

QueueItemType Queue::getBack()
{
	return backNode->stationIndex;
}

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

Queue Queue::clone(Queue original, Queue newQueue)
{
	for (int i = 0; i < original.getLength(); i++)
	{
		newQueue.enqueue(original.get(i));
	}
	return newQueue;
}