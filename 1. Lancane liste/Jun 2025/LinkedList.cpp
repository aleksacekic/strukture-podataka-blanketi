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

double Calculate(SLList& lsIzmenjeni) {

    while (lsIzmenjeni.head != nullptr) {
        Node* studentZaUbacivanje = lsIzmenjeni.head;
        lsIzmenjeni.head = lsIzmenjeni.head->next;
        studentZaUbacivanje->next = nullptr;

        Node* curr = this->head;
        Node* prev = nullptr;

        while (curr != nullptr && curr->points < studentZaUbacivanje->points) {
            prev = curr;
            curr = curr->next;
        }

	//nas student ide na pocetak - najmanje bod
        if (prev == nullptr) {
            studentZaUbacivanje->next = this->head;
            this->head = studentZaUbacivanje;
        } 
        //nas student ide u sredinu/kraj
        else {
            prev->next = studentZaUbacivanje;
            studentZaUbacivanje->next = curr;
        }
    }

    double suma = 0;
    int brojac = 0;
    Node* temp = this->head;
    while (temp != nullptr) {
        suma += temp->points;
        brojac++;
        temp = temp->next;
    }

    if (brojac == 0) return 0.0;
    return suma / brojac;
}
