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

void moveGroupBefore(char grToMove, char grFixed) {
    if (grToMove == grFixed || head == nullptr) return;

    Node *startToMove = nullptr, *endToMove = nullptr, *prevToMove = nullptr;
    Node *lastFixed = nullptr;
    
    Node *curr = head;
    Node *prev = nullptr;

    while (curr != nullptr) {
        if (curr->podgrupa == grToMove) {
            if (startToMove == nullptr) {
                startToMove = curr;
                prevToMove = prev; 
            }
            endToMove = curr;
        }
        
        if (curr->podgrupa == grFixed) {
            lastFixed = curr;
        }

        prev = curr;
        curr = curr->next;
    }

    if (startToMove == nullptr || lastFixed == nullptr) return;

    if (lastFixed->next == startToMove) return;

    if (prevToMove == nullptr) {
        head = endToMove->next;
    } else {
        prevToMove->next = endToMove->next;
    }

    endToMove->next = lastFixed->next;
    lastFixed->next = startToMove;
}
