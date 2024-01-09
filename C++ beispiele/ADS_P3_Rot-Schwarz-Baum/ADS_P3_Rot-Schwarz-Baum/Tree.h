/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Tree {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	TreeNode* anker = nullptr;
	int NodeIDCounter = 1;

	bool searchTree(TreeNode* act, string Name);

	void preOrder(TreeNode * act);

	//
	////////////////////////////////////	

public:
	///////////////////////////////////////
	// Ihr Code hier:	
	Tree();

	bool balanceTree();

	int height(TreeNode* node);

	void printLevelOrder();

	void printExactLevel(TreeNode * act, int printLevel, int currentLevel);

	bool rotateTreeRight(TreeNode *, TreeNode*);

	bool rotateTreeLeft(TreeNode*, TreeNode*);
	
	TreeNode* getParent(TreeNode* act, TreeNode* child);

	void addNode(string Name, int Alter, double Einkommen, int PLZ);

	void deleteNode(int NodePosID);

	bool searchNode(string Name);

	void printAll();
	

	//
	////////////////////////////////////
	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
	friend TreeNode * get_anker(Tree& TN);
};
