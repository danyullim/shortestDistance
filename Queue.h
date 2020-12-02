#ifndef QUEUE_TYPE_H
#define QUEUE_TYPE_H

#include <iostream>
#include <cassert>

using namespace std;

template <class Type>
class queue
{
public:
	queue(int queueSize = 100);

	bool is_empty() const;
	bool is_full() const;

	void enqueue(const Type& element);
	void dequeue();

	Type front() const;
	Type back() const;

	~queue();

private:
	int maxQueueSize;  //variable to store the maximum queue size
	int count;         //variable to store the number of elements in the queue
	int queueFront;    //location of the front element
	int queueRear;     //location of the last element
	Type* list;        //pointer to the array; the queue
};

#endif // !QUEUE_TYPE_H


template <class Type>
queue<Type>::queue(int queueSize) {
	if (queueSize <= 0) {
		maxQueueSize = 100;
	}
	else {
		maxQueueSize = queueSize;   //set maxQueueSize to
	}

	queueFront = 0;					//initialize queueFront
	queueRear = maxQueueSize - 1;   //initialize queueRear
	count = 0;
	list = new Type[maxQueueSize];
}

template <class Type>
bool queue<Type>::is_empty() const {
	return (count == 0);
}

template <class Type>
bool queue<Type>::is_full() const {
	return (count == maxQueueSize);
}

template <class Type>
void queue<Type>::enqueue(const Type& queueElement) {
	if (!is_full()) {
		queueRear = (queueRear + 1) % maxQueueSize; //use the
		count++;
		list[queueRear] = queueElement;
	}
	else {
		cout << "Cannot add to a full queue." << endl;
	}
}

template <class Type>
void queue<Type>::dequeue() {
	if (!is_empty()) {
		count--;
		queueFront = (queueFront + 1) % maxQueueSize; //use the
	}
	else {
		cout << "Cannot remove from an empty queue" << endl;
	}
}

template <class Type>
Type queue<Type>::front() const {
	assert(!is_empty());
	return list[queueFront];
}

template <class Type>
Type queue<Type>::back() const {
	assert(!is_empty());
	return list[queueRear];
}

template <class Type>
queue<Type>::~queue() {
	delete[] list;
}