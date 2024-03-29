#include <string>
#include <iostream>

#include "queue.h"
#include "node.h"

// Instantiate the queue with the head pointing to nothing
template <typename T>
Queue<T>::Queue() {
    head = nullptr;
    tail = nullptr;
}

// Creates a new node and adds it to the queue
template <typename T>
void Queue<T>::enqueue(Node<T>* newNode) {    
    if (isEmpty()) {
        // Immediately set the head and tail to be the new node if we are empty
        head = newNode;
        tail = newNode;
    } else {
        // Have the old tail to point to the new node and then update the pointer
        tail->next = newNode;
        tail = newNode;
    }
    // printQueue();
}

// Removes the front node from the queue
template <typename T>
Node<T>* Queue<T>::dequeue() {
    if (isEmpty()) {
        // Throw an exception if the queue is already empty
        throw std::invalid_argument("Tried to dequeue from an empty queue.");
    } else {
        // We need to collect the data in the node before removing it from the queue
        Node<T>* frontNode = head;
        head = head->next;
        if (head == nullptr) {
            // Tail has to become nullptr because the queue is now empty
            tail = nullptr;
        }

        // We have to remove whatever next is pointing to because the node is no longer
        // a part of the linked list for the stack
        frontNode->next = nullptr;

        return frontNode;
    }
}

// Checks to see if the queue is empty or not
template <typename T>
bool Queue<T>::isEmpty() {
    return head == nullptr;
}

template <typename T>
void Queue<T>::printQueue() {
    // Get the head of the queue and iterate through, printing the data in each node
    Node<T>* cur = head;
    while (cur != nullptr) {
        std::cout << cur->data << " -> ";
        cur = cur->next;
    }
    // Finish the queue printing
    std::cout << "nullptr" << std::endl;
}

// Define acceptable data types that the Queue can accept for the template
template class Queue<std::string>;
template class Queue<char>;