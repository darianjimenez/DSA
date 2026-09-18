#include "stack.hpp"
#include <cassert>

int main() {
    Stack stack;

    assert(stack.isEmpty());

    stack.push(10);
    stack.push(20);

    assert(stack.peek() == 20);
    assert(stack.pop() == 20);
    assert(stack.peek() == 10);
    assert(stack.pop() == 10);

    assert(stack.isEmpty());

    return 0;
}