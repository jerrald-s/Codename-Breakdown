#pragma once
#include <string>

typedef int StaCodeType;
typedef string LineType;
typedef string NameType;

struct BinaryNode
{
	LineType   line;
	StaCodeType   item;	// data item
	NameType   name;
	BinaryNode *left;	// pointer pointing to left subtree
	BinaryNode *right;	// pointer pointing to right subtree
};
