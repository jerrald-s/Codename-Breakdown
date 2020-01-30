#include "pch.h"
#include "Graph.h"


//graph::graph(Edge edges[], int noOfEdges, int noOfVertex)
//{
//	////creates number of Nodes according to number of vertex
//	//head = new Node*[noOfVertex]();
//	//this->numOfNodes = noOfVertex;
//
//	////initialize head pointer for all vertex
//	//for (int i = 0; i < noOfVertex; i++) {
//	//	head[i] = nullptr;
//	//}
//
//	////add edges to the directed graph
//	//for (unsigned i = 0; i < noOfEdges; i++) {
//	//	string src = edges[i].src;
//	//	string dest = edges[i].dest;
//	//	int srcc = edges[i].srcc;
//
//	//	Node* newNode = getAdjListNode(dest, head[srcc]);
//	}
//}

Graph::Graph()
{
	noOfVectors = 0;
}

Graph::~Graph()
{
}

Graph* Graph::newGraph(int noOfVectors) {
	Graph *graph = new Graph;
	graph->noOfVectors = noOfVectors;
	graph->array = new AdjList[noOfVectors];
	for (int i = 0; i < noOfVectors; i++) {
		graph->array[i].head = nullptr;
	}
	return graph;
}

