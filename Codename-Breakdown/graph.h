#pragma once
#include <iostream>
using namespace std;

typedef struct graph Graph;

//val -> value, dest-> destination, src-> source
struct Node {
	string station;
	Node* next;
};

struct Edge {
	string src, dest;
};

struct adjList {
	Node* head;
};

class graph
{
private:
	Node* getAdjListNode(string dest, Node* head) {
		Node* newNode = new Node;
		newNode->station = dest;

		newNode->next = head;

		return newNode;
	}

	int numOfNodes;
	

public:
	Node**head;
	graph(Edge edges[], int noOfEdges, int noOfVertex); //constructor
	~graph(); //deconstructor
};

