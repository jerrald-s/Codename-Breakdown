#pragma once
#include<iostream>
using namespace std;

#include "BinaryNode.h"

class BST
{
private:

	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST();

	// search an item in the binary search tree
	BinaryNode* search(StaCodeType target);
	BinaryNode* search(BinaryNode* root, StaCodeType target);

	// insert an item to the binary search tree
	void insert(StaCodeType item, LineType line, NameType name);
	void insert(BinaryNode* &root, StaCodeType item, LineType line, NameType name);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the binary search tree in preorder
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	void postorder();
	void postorder(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();

	// count the number of nodes in the binary search tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// compute the height of the binary search tree
	//int getHeight();
	//int getHeight(BinaryNode* t);

	// check if the binary search tree is balanced
	//bool isBalanced();
	//bool isBalanced(BinaryNode *t);
};

