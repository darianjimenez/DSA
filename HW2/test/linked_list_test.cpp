#include "linked_list.hpp"
#include <cassert>

int main() {
    LinkedList list;

    assert(list.isEmpty());

    list.pushFront(10);
    assert(list.peekFront() == 10);

    list.pushBack(20);
    assert(list.peekBack() == 20);

    assert(list.popFront() == 10);
    assert(list.peekFront() == 20);

    assert(list.popBack() == 20);
    assert(list.isEmpty());

    return 0;
}