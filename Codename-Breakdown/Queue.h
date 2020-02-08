// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
using namespace std;
#include "List.h"

typedef int QueueItemType;

class Queue
{
private:
	struct QueueNode
	{
		QueueItemType stationIndex;	// item
		QueueNode     *next;	// pointer pointing to next item
	};

	QueueNode *frontNode;	// point to the first item
	QueueNode *backNode;	// point to the first item


public:
	// constructor
	Queue();

	~Queue();

	// enqueue (add) item at the back of queue
	bool enqueue(QueueItemType item);

	// dequeue (remove) item from front of queue
	bool dequeue();

	// dequeue (remove) and retrieve item from front of queue
	bool dequeue(QueueItemType &item);

	// retrieve (get) item from front of queue
	void getFront(QueueItemType &item);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	List displayItems(List list);

	QueueItemType getBack();

	int getLength();

	QueueItemType get(int index);

	Queue clone(Queue original, Queue newQueue);
};
