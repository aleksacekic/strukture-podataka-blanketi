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

void groupSegments(int k) {
    if (head == nullptr || k <= 0) return;

    //kraj naseg segmenta
    Node* prev = head;
    for (int i = 1; i < k; i++) {
        if (prev->next == nullptr) return;
        prev = prev->next;
    }

    //petlja za ostatak liste
    while (prev != nullptr && prev->next != nullptr) {
        Node* p1 = head;
        Node* p2 = prev->next;
        int count = 0;

	//poredimo
        while (count < k && p2 != nullptr && p1->info == p2->info) {
            p1 = p1->next;
            p2 = p2->next;
            count++;
        }

        //ako smo nasli da se poklapa
        if (count == k) {
            Node* zaBrisanje = prev->next;
            prev->next = p2;

            //brisanje
            for (int i = 0; i < k; i++) {
                Node* temp = zaBrisanje;
                zaBrisanje = zaBrisanje->next;
                delete temp;
            }             
        } 
        else {
            prev = prev->next;
        }
    }
}
