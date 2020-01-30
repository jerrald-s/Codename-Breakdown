#pragma once
#include <iostream>
using namespace std;

//val -> value, dest-> destination, src-> source
//struct Node {
//	string station;
//	int weight;
//	Node* next;
//};
//
//struct Edge {
//	string src, dest;
//	int srcc;
//};
//
//struct adjList {
//	Node* head;
//};



class Graph
{
private:
	struct AdjListNode {
		string station;
		int data;
		AdjListNode* next;
	};

	struct AdjList {
		AdjListNode* head;
	};

	int noOfVectors;
	AdjList *array;

public:
	Graph(); //constructor
	~Graph(); //deconstructor
	Graph* newGraph(int noOfVectors);
	void addEdge(Graph g, int src, int dest);
};