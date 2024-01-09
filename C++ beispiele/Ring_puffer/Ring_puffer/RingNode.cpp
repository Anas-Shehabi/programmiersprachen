#include <iostream>
#include "RingNode.h"
using namespace std;

RingNode::RingNode() {
	OldAge = 0;
	Description = "";
	SymbolicData = "";
	Next = nullptr;
}

RingNode::RingNode(int age, string des, string data) {
	this->OldAge = age;
	this->Description = des;
	this->SymbolicData = data;
}

int RingNode::getAge() {
	return OldAge;
}
void RingNode::setAge(int age) {
	OldAge = age;
}

string RingNode::getDescription() {
	return Description;
}

void RingNode::setDescription(string des) {
	Description = des;
}
string RingNode::getData() {
	return SymbolicData;
}
void RingNode::setData(string data) {
	SymbolicData = data;
}
RingNode* RingNode::getNext() {
	return Next;
}
void RingNode::setNext(RingNode* next) {
	Next = next;
}