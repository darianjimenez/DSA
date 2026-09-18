#pragma once
#include <iostream>

class LinkedList {
private:
    struct Node {
        int data;
        Node *next;
        Node *prev;

        // Create new node
        Node(int val) {
            data = val;
            next = NULL; // Null because not connected yet
            prev = NULL; // Null because not connected yet
        }
    };

    Node *head; // points to first node
    Node *tail; // points to last node

public:
    // Create empty linked list
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    /* Adds the element [data] to the front of the linked list. */
    void pushFront(int data) {
        Node *newNode = new Node(data); // Create a new node w/ value

        // If list empty, new node is the first AND last node
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            return;
        }

        newNode->next = head; // New node points forward to current head
        head->prev = newNode; // Current head points backwards to new node
        head = newNode;       // New node is now new head
    }

    /* Adds the element [data] to the back of the linked list. */
    void pushBack(int data) {
        Node *newNode = new Node(data); // Create a new node w/ value

        // If list empty, new node is the first AND last node
        if (tail == NULL) {
            head = newNode;
            tail = newNode;
            return;
        }

        tail->next = newNode; // Tail should point forward to new node
        newNode->prev = tail; // New node should point backward to current tail
        tail = newNode;       // New node is now new tail
    }

    /* Removes an element from the front of the list. If the list is empty, it is unchanged.
       @return the value at the front of the list or nil if none exists */
    int popFront() {
        if (head == NULL) {
            return 0; // Return 0 of list empty
        }

        int val = head->data; // Save val to be able to return it later
        Node *oldHead = head; // Save current head so we can delete it

        // If only one node in the list:
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            head = head->next; // Move head to next node
            head->prev = NULL; // No prev node because head is the first node
        }

        // Free memory used by old head
        delete oldHead;
        return val;
    }

    /* Removes an element from the back of the list. If the list is empty, it is unchanged.
       @return the value at the back of the list or nil if none exists */
    int popBack() {
        if (tail == NULL) {
            return 0; // Return 0 of list empty
        }

        int val = tail->data; // Save val to be able to return it later
        Node *oldTail = tail; // Save current tail so we can delete it

        // If only one node in the list:
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            tail = tail->prev; // Move tail to prev node
            tail->next = NULL; // Not pointing to next node, because its the last node
        }

        // Free memory used by old tail
        delete oldTail;
        return val;
    }

    /* @return the value at the front of the list or nil if none exists */
    int peekFront() {
        if (head == NULL) {
            return 0;
        }
        return head->data;
    }

    /* @return the value at the back of the list or nil if none exists */
    int peekBack() {
        if (tail == NULL) {
            return 0;
        }

        return tail->data;
    }

    /* @return true if the list is empty and false otherwise */
    bool isEmpty() {
        if (head == NULL) {
            return true; // List must be empty if head is null
        }
        return false;
    }
};