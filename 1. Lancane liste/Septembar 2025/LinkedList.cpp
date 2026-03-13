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

void transpose(int key) {
    Node* curr = head;
    Node* prev = nullptr;
    Node* prevprev = nullptr;

    while (curr) {
        if (curr->info == key) {       
            if (prev == nullptr) {
                prevprev = prev;
                prev = curr;
                curr = curr->next;
                continue; 
            }

            else if (prevprev == nullptr) {
                Node* nxt = curr->next; 
                head = curr;
                curr->next = prev;
                prev->next = nxt; 
                
                prevprev = curr;
                //prev ostaje prev
                curr = nxt;
                continue;
            }

            else if (curr->next == nullptr) {
                prevprev->next = curr;
                curr->next = prev;
                prev->next = nullptr; 
                
                prevprev = curr;
                prev = prev;
                curr = nullptr; 
                continue;
            }

            else {
                Node* nxt = curr->next;
                prevprev->next = curr;
                curr->next = prev;
                prev->next = nxt;

                prevprev = curr;
                //prev ostaje prev
                curr = nxt;
                continue;
            }
        }

        prevprev = prev;
        prev = curr;
        curr = curr->next;
    }
}
