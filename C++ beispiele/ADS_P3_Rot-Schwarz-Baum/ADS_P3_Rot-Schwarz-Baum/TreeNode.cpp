/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>


////////////////////////////////////
// Ihr Code hier:
TreeNode::TreeNode(int NodePosID, int NodeID, string Name, int Alter, double Einkommen, int PLZ)
{
	this->NodePosID = NodePosID;
	this->NodeID = NodeID;
	this->Name = Name;
	this->Alter = Alter;
	this->Einkommen = Einkommen;
	this->PLZ = PLZ;
}

int TreeNode::getNodePosID()
{
	return NodePosID;
}

int TreeNode::getNodeID()
{
	return NodeID;
}

bool TreeNode::getRed()
{
	return red;
}

void TreeNode::setRed(bool yes)
{
	this->red = yes;

}

string TreeNode::getName()
{
	return Name;
}

void TreeNode::setName(string Name)
{
	this->Name = Name;
}

int TreeNode::getAlter()
{
	return Alter;
}

void TreeNode::setAlter(int Alter)
{
	this->Alter = Alter;
}

double TreeNode::getEinkommen()
{
	return Einkommen;
}

void TreeNode::setEinkommen(double Einkommen)
{
	this->Einkommen = Einkommen;
}

int TreeNode::getPLZ()
{
	return PLZ;
}

void TreeNode::setPLZ(int PLZ)
{
	this->PLZ = PLZ;
}

TreeNode* TreeNode::getLeft()
{
	return left;
}

TreeNode* TreeNode::getRight()
{
	return right;
}

void TreeNode::setLeft(TreeNode* LeftNode)
{
	this->left = LeftNode;
}

void TreeNode::setRight(TreeNode* RightNode)
{
	this->right = RightNode;
}

void TreeNode::print()
{

}


//
////////////////////////////////////
