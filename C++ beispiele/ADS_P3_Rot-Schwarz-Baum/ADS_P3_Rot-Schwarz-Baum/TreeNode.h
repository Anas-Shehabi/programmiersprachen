/*************************************************
* ADS Praktikum 2.2
* TreeNode.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	int NodePosID;
	int NodeID;
	bool red;
	string Name;
	int Alter;
	double Einkommen;
	int PLZ;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	//
	////////////////////////////////////

public:
	///////////////////////////////////////
	// Ihr Code hier:
	TreeNode(int NodePosID, int NodeID, string Name, int Alter, double Einkommen, int PLZ);

	int getNodePosID();

	int getNodeID();

	bool getRed();

	void setRed(bool yes);


	string getName();

	void setName(string Name);

	int getAlter();

	void setAlter(int Alter);

	double getEinkommen();

	void setEinkommen(double Einkommen);

	int getPLZ();

	void  setPLZ(int PLZ);

	TreeNode* getLeft();

	TreeNode* getRight();

	void setLeft(TreeNode* LeftNode);

	void setRight(TreeNode* RightNode);

	void print();


	//
	////////////////////////////////////
};
