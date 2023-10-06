#include "queue.h"
#include <iostream>

void Queue::ins(int num) {
	queue[size++] = num;
}

void Queue::del() {
	for (int i = 0; i < size; i++) {
		queue[i] = queue[i + 1];
	}
	size--;
}

bool Queue::isEmpty() {
	return size == 0;
}

void Queue::printQ() {
	for (int i = 0; i < size;i++) {
		std::cout << queue[i] << "  ";
	}

	std::cout << std::endl;
}