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

void reverseSegment(Node* &head, int k, int j) {
    if (head == nullptr) return;

    //trazimo pocetak i kraj
    Node* startNode = nullptr;
    Node* endNode = nullptr;
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->info == k) startNode = temp;
        if (temp->info == j) endNode = temp;
        temp = temp->next;
    }

    //ako nemamo oba, kraj
    if (startNode == nullptr || endNode == nullptr || startNode == endNode) return;

    //cuvamo pre i posle segmenta
    Node* preSegmenta = startNode->prev;
    Node* posleSegmenta = endNode->next;

    //ovde cemo 'obrnemo' vezu:)
    Node* curr = startNode;
    Node* stopNode = endNode->next; // granica dokle idemo

    while (curr != stopNode) {
        Node* sledeciOriginalni = curr->next; //upamtimo ga jer ce curr-<next da se menja!!
        
        curr->next = curr->prev; 
        curr->prev = sledeciOriginalni;
        
        curr = sledeciOriginalni;
    }

   
    // povezujemo na kraju
    if (preSegmenta != nullptr) {
        preSegmenta->next = endNode;
    } else {
        head = endNode;
    }
    endNode->prev = preSegmenta;

    
    startNode->next = posleSegmenta;
    if (posleSegmenta != nullptr) {
        posleSegmenta->prev = startNode;
    }
}
