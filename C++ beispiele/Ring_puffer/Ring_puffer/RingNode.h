#pragma once
#include <string>
using namespace std;

class RingNode {
private:
	int OldAge;
	string Description;
	string SymbolicData;
	RingNode* Next;

public:
	RingNode();
	RingNode(int, string, string);
	int getAge();
	void setAge(int Age);
	string getDescription();
	void setDescription(string des);
	string getData();
	void setData(string dat);
	RingNode* getNext();
	void setNext(RingNode*);


};