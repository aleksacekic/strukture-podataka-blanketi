#include "LinkedList.h"

int main() {
	try {

		LinkedList lista;
		lista.addToHead(15);
		lista.addToHead(1);
		lista.addToHead(9);
		

		lista.printAll();

		
		//lista.void reverseSegment(Node* &head, int k, int j)
		lista.printAll();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}