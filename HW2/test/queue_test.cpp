#include "queue.hpp"
#include <cassert>

int main() {
    Queue queue;

    assert(queue.isEmpty());

    queue.enqueue(10);
    queue.enqueue(20);

    assert(queue.peek() == 10);
    assert(queue.dequeue() == 10);
    assert(queue.peek() == 20);
    assert(queue.dequeue() == 20);

    assert(queue.isEmpty());

    return 0;
}