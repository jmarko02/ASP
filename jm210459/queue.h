#ifndef _queue_h_
#define _queue_h_

class Queue {
private:
	int size;
	int queue[1024];

public:
	Queue():size(0){}

	void ins(int num);
	void del();

	int front() const { return queue[0]; }

	bool isEmpty();
	void printQ();
};

#endif