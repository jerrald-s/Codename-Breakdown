#include "pch.h"
#include "BST.h"

#define max(x,y) ((x > y)? x : y)

// constructor
BST::BST()
{
	root = NULL;
}

// search an item in the binary search tree
BinaryNode* BST::search(StaCodeType target)
{
	return search(root, target);
}

BinaryNode* BST::search(BinaryNode* t, StaCodeType target)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		if (t->item == target)	// item found
			return t;
		else
			if (target < t->item)	// search in left subtree
				return search(t->left, target);
			else // search in right subtree
				return search(t->right, target);
	}
}

// insert an item to the binary search tree
void BST::insert(StaCodeType item, LineType line, NameType name)
{
	insert(root, item, line, name);
}

void BST::insert(BinaryNode* &t, StaCodeType item, LineType line, NameType name)
{
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = item;
		newNode->line = line;
		newNode->name = name;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else
		if (item < t->item)
			insert(t->left, item, line, name);  // insert in left subtree
		else
			insert(t->right, item, line, name); // insert in right subtree
}

// traverse the binary search tree in inorder
void BST::inorder()
{
	if (isEmpty())
		cout << "No line found" << endl;
	else
		inorder(root);
}

void BST::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		if (t->item != "")
			cout << t->line << t->item << " " << t->name << endl;
		else
			cout << t->line << " " << t->name << endl;
		inorder(t->right);

	}
}
// traverse the binary search tree in preorder
void BST::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void BST::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		cout << t->item << endl;
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void BST::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void BST::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		cout << t->item << endl;
	}
}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}

int BST::countNodes()
{
	return countNodes(root);
}

int BST::countNodes(BinaryNode* t)
{
	int count = 1;
	if (t->left != NULL)
	{
		count += countNodes(root->left);
	}
	if (t->right != NULL)
	{
		count += countNodes(root->right);
	}
	return count;
}

