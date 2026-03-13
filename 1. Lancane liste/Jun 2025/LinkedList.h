#pragma once
#include "Node.h"

class LinkedList
{
private:
	Node* head;

public:
	LinkedList();
	~LinkedList();

	bool isEmpty();
	int deleteFromHead();
	void addToHead(int el);
	void printAll();
	double Calculate(SLList& lsIzmenjeni);
};

