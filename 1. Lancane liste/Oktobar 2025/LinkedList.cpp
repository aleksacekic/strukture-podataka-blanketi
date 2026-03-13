#include "LinkedList.h"

LinkedList::LinkedList()
{
	head = nullptr;
}

LinkedList::~LinkedList()
{
	while (!isEmpty())
		int el = deleteFromHead();
}

inline bool LinkedList::isEmpty()
{
	return (head == nullptr);
}

int LinkedList::deleteFromHead()
{
	if (isEmpty())
		throw std::exception("Lista je prazna.");

	Node* tmp = head;
	int el = tmp->info;
	head = head->next;
	delete tmp;
	return el;
}

void LinkedList::addToHead(int el)
{
	head = new Node(el, head);
}

void LinkedList::printAll()
{
	Node* tmp = head;
	while (tmp != nullptr) {
		tmp->print();
		tmp = tmp->next;
	}

	std::cout << std::endl;
}

void switchNodes(int key1, int key2) {
    if (head == nullptr || key1 == key2) return;

    Node *prev1 = nullptr, *curr1 = head;
    
    while (curr1 != nullptr && curr1->info != key1) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    Node *prev2 = curr1;
    Node *curr2;
    if (curr1 != nullptr) {
        curr2 = curr1->next;
    } else {
        curr2 = nullptr;
    }
    

    while (curr2 != nullptr && curr2->info != key2) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (curr1 == nullptr || curr2 == nullptr) return;

    if (prev1 != nullptr) {
        prev1->next = curr2;
    } else {
        head = curr2;
    }

    if (curr1->next == curr2) {
        curr1->next = curr2->next;
        curr2->next = curr1;
    } else {
        Node* tempNext = curr1->next;
        
        curr1->next = curr2->next;
        prev2->next = curr1;
        curr2->next = tempNext;
    }
}
