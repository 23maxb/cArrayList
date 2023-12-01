#include <stdio.h>
#include <assert.h>
#include "list.c"

void testCreateDestroyList() {
    LIST* list = createList();
    assert(list != NULL); // Test list creation

    destroyList(list); // Test list destruction
}

void testAddFirstLast() {
    LIST* list = createList();
    int items[5] = {1, 2, 3, 4, 5};

    // Test adding to the front
    for (int i = 0; i < 5; i++) {
        addFirst(list, &items[i]);
    }
    assert(numItems(list) == 5); // Check size

    // Test adding to the end
    for (int i = 0; i < 5; i++) {
        addLast(list, &items[i]);
    }
    assert(numItems(list) == 10); // Check size

    destroyList(list);
}

void testRemoveFirstLast() {
    LIST* list = createList();
    int items[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        addLast(list, &items[i]);
    }

    // Test removing from the front
    for (int i = 0; i < 5; i++) {
        assert(*(int*) removeFirst(list) == items[i]);
    }

    // Test removing from the end
    for (int i = 0; i < 5; i++) {
        addFirst(list, &items[i]);
    }
    for (int i = 0; i < 5; i++) {
        assert(*(int*) removeLast(list) == items[i]);
    }

    destroyList(list);
}

void testGetFirstLastItem() {
    LIST* list = createList();
    int items[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        addLast(list, &items[i]);
    }

    assert(*(int*) getFirst(list) == 1);
    assert(*(int*) getLast(list) == 5);

    destroyList(list);
}

void testGetSetItem() {
    LIST* list = createList();
    int items[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        addLast(list, &items[i]);
    }

    for (int i = 0; i < 5; i++) {
        assert(*(int*) getItem(list, i) == items[i]);
    }

    int newItem = 10;
    setItem(list, 2, &newItem);
    assert(*(int*) getItem(list, 2) == newItem);

    destroyList(list);
}

int main() {
    LIST* list = createList();
    int items[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        addLast(list, &items[i]);
    }

    // Test removing from the front
    for (int i = 0; i < 5; i++) {
        assert(*(int*) removeFirst(list) == items[i]);
    }
    printf("ok\n\n");
    // Test removing from the end
    for (int i = 0; i < 5; i++) {
        addFirst(list, &items[i]);
    }
    printf("arrays:  %d\n", list->head->prev->capacity);
    printf("valhere:  %d\n", *(int*) list->head->data[0]);
    printf("ok1512651\n\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", *(int*) getItem(list, i));
    }
    printf("-----------\n\n");

    for (int i = 0; i < 5; i++) {
        assert(*(int*) removeLast(list) == items[i]);
    }

    destroyList(list);

    printf("All tests passed successfully.\n");
    return 0;
}
