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

void removeSegment(Node* &head, int k, int j) {
    Node* curr = head;

    while (curr != nullptr) {
        //pocetak
        if (curr->info == k) {
            Node* startNode = curr;
            Node* endNode = nullptr;
            
            //kraj
            Node* temp = startNode;
            while (temp != nullptr) {
                if (temp->info == j) {
                    endNode = temp;
                    break;
                }
                temp = temp->next;
            }

            //ako imamo segment
            if (endNode != nullptr) {
                Node* preSegmenta = startNode->prev;
                Node* posleSegmenta = endNode->next;

               
                if (preSegmenta != nullptr) {
                    preSegmenta->next = posleSegmenta;
                } else {
                    head = posleSegmenta;
                }

                
                if (posleSegmenta != nullptr) {
                    posleSegmenta->prev = preSegmenta;
                }

                //stvarno brisanje
                Node* zaBrisanje = startNode;
                while (zaBrisanje != posleSegmenta) {
                    Node* sledeci = zaBrisanje->next;
                    delete zaBrisanje;
                    zaBrisanje = sledeci;
                }

                //nastavljamo posle obrisanog
                curr = posleSegmenta;
                continue;
            }
        }
        
        if (curr != nullptr) curr = curr->next;
    }
}
