#ifndef __Queue_H__
#define __Queue_H__

template <typename T>
class Queue{
	struct Node{
		T data;
		Node *next;
		Ndoe (T data);
	}
public:
	Queue();
	Queue(const Queue& queue);
	~Queue();
	void enqueue(T);
	T dequeue();
	bool isEmpty();
	Queue& operator=(const Queue& queue);
private:
	Node *head = nullptr;
	Node *tail = nullptr;
};

#endif
