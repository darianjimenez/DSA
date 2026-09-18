#include "linked_list.hpp"

class Stack {
private:
    LinkedList list;

public:
    // Add [data] to the top of the stack
    void push(int data) {
        list.pushFront(data);
    }

    // Remove the element at the top of the stack.  If the stack is empty, it remains unchanged.
    // @return the value at the top of the stack or nil if none exists
    int pop() {
        return list.popFront();
    }

    // @return the value on the top of the stack or nil if none exists
    int peek() {
        return list.peekFront();
    }

    // @return true if the stack is empty and false otherwise
    bool isEmpty() {
        return list.isEmpty();
    }
};