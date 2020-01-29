#include "pch.h"
#include "graph.h"


graph::graph(Edge edges[], int noOfEdges, int noOfVertex)
{
	//creates number of Nodes according to number of vertex
	head = new Node*[noOfVertex]();
	this->numOfNodes = noOfVertex;

	//initialize head pointer for all vertex
	for (int i = 0; i < noOfVertex; i++) {
		head[i] = nullptr;
	}

	//add edges to the directed graph
	for (unsigned i = 0; i < noOfEdges; i++) {
		string src = edges[i].src;
		string dest = edges[i].dest;

		Node* newNode = getAdjListNode(dest, head[i]);
	}
}


graph::~graph()
{
}
