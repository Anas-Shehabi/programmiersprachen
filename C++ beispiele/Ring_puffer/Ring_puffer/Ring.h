#pragma once
#include "RingNode.h"

class Ring {
private:
	int AnzahlNodes;
	RingNode* anker;

public:

	Ring();
	void addNode(string, string);
	bool search(string);
	void print();
};