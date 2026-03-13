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

void partitionList(Node** head, int pivot) {
    Node* lessHead = nullptr;
    Node* geHead = nullptr;
    Node* lessTail = nullptr;
    Node* geTail = nullptr;
    Node* curr = *head; //jer je gore Node**

    while(curr) {
        Node* sledeci = curr->next;
        curr->next = nullptr;

        if(curr->info < pivot) {
            if(!lessHead) {
                lessHead = lessTail = curr;
            } else {
                lessTail->next = curr;
                lessTail = curr;
            }
        } else {
            if(!geHead) {
                geHead = geTail = curr;
            } else {
                geTail->next = curr;
                geTail = curr;
            }
        }
        curr = sledeci;
    }

    if (lessHead != nullptr) {
        lessTail->next = geHead;
        *head = lessHead;
    } else {
        *head = geHead;
    }
}
