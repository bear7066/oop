#ifndef __QUEUE_H__
#define __QUEUE_H__

template <typename T>
class Queue {
    struct Node {
        T data;
        Node *next;
        Node(T data);
    };
public:
    // normal constructor
	Queue(){};

    // copy constructor
	Queue(const Queue& queue);
    
	// destructor
	~Queue();

    void enqueue(T);
    T dequeue();
    bool isEmpty();
    
	Queue& operator=(const Queue& queue);

private:
    Node *head = nullptr;
    Node *tail = nullptr;
};

#endif /* __QUEUE_H__ */
