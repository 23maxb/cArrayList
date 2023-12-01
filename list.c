//filename: list.c
/**
 * Defines an implementation for an arrayList.
 * This implementation is based on the list.h file provided by the professor
 * The ArrayList Implementation uses a linked list of arrays to store the data.
 * The only missing method is addAtIndex() which was not required in the list.h file.
 *
 * @author Max Blennemann
 * @version 11/29/23
 */
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"


typedef struct list {
    int count;
    struct node* head;
} LIST;

typedef struct node {
    void** data;
    unsigned firstIndex;
    unsigned count;
    unsigned capacity;
    struct node* next;
    struct node* prev;
} NODE;

#define DEFAULT_SUBARRAY_LENGTH 2

/**
 * Creates a new list and returns a pointer to it.
 *
 * @return the new list
 * @timeComplexity O(1)
 */
LIST* createList() {
    LIST* lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->data = malloc(DEFAULT_SUBARRAY_LENGTH * sizeof(void*));
    assert(lp->head->data != NULL);
    lp->head->capacity = DEFAULT_SUBARRAY_LENGTH;
    lp->head->next = lp->head;
    lp->head->firstIndex = 0;
    lp->head->count = 0;
    lp->head->prev = lp->head;
    return lp;
}

/**
 * Destroys the list and frees all memory associated with it.
 *
 * @param lp the list to destroy
 * @timeComplexity O(N)
 */
void destroyList(LIST* lp) {
    assert(lp != NULL);
    NODE* np = lp->head->next;
    while (np != lp->head) {
        NODE* next = np->next;
        free(np->data);
        free(np);
        np = next;
    }
    free(lp->head->data);
    free(lp->head);
    free(lp);
}

/**
 * Returns the number of items in the list.
 *
 * @param lp the list to get the number of items from
 * @return the number of items in the list
 * @timeComplexity O(1)
 */
int numItems(LIST* lp) {
    assert(lp != NULL);
    return lp->count;
}

/**
 * Adds an item to the front of the list.
 *
 * @param lp the list to add the item to
 * @param item the item to add (cant be null)
 * @timeComplexity O(1)
 */
void addFirst(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(item != NULL);
    if (lp->head->count == lp->head->capacity) {
        NODE* np = malloc(sizeof(NODE));
        assert(np != NULL);
        np->data = malloc(lp->head->capacity * 2 * sizeof(void*));
        assert(np->data != NULL);
        np->capacity = lp->head->capacity * 2;
        np->next = lp->head;
        np->prev = lp->head->prev;
        np->firstIndex = 0;
        np->count = 0;
        lp->head = np;
    }
    if (lp->head->firstIndex == 0) {
        lp->head->firstIndex = DEFAULT_SUBARRAY_LENGTH - 1;
    } else {
        lp->head->firstIndex--;
    }
    lp->head->count++;
    lp->head->data[lp->head->firstIndex] = item;
    lp->count++;
}

/**
 * Adds an item to the end of the list.
 *
 * @param lp the list to add the item to
 * @param item the item to add (cant be null)
 * @timeComplexity O(N)
 */
void addLast(LIST* lp, void* item) {
    printf("addLast\n");
    assert(lp != NULL);
    assert(item != NULL);

    if (lp->head->prev->count == lp->head->prev->capacity) {
        NODE* np = malloc(sizeof(NODE));
        assert(np != NULL);
        np->data = malloc(lp->head->prev->capacity * 2 * sizeof(void*));
        assert(np->data != NULL);
        np->next = lp->head;
        np->prev = lp->head->prev;
        np->firstIndex = 0;
        np->count = 0;
        np->capacity = lp->head->prev->capacity * 2;
        lp->head->prev->next = np;
        lp->head->prev = np;
    }
    lp->head->prev->data[(lp->head->prev->firstIndex + lp->head->prev->count) % lp->head->prev->capacity] = item;
    lp->head->prev->count++;
    lp->count++;
}

/**
 * Removes the item at the front of the list.
 *
 * @param lp the list to add the item to
 * @param item the item to add (cant be null)
 * @timeComplexity O(1)
 */
void* removeFirst(LIST* lp) {
    printf("removeFirst\n");
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE* front = lp->head;
    while (front->count == 0) {
        front = front->next;
    }
    void* item = front->data[front->firstIndex];
    front->firstIndex = (front->firstIndex + 1) % front->capacity;
    front->count--;
    lp->count--;
    return item;
}

/**
 * Removes the last element from the array.
 *
 * @param lp the list to remove the last element from
 * @return the removed element
 * @timeComplexity O(N)
 */
void* removeLast(LIST* lp) {
    printf("removeLast\n");
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE* a = lp->head->prev;
    while (a->count == 0) {
        a = a->prev;
    }
    void* item = a->data[(a->firstIndex + a->count - 1) % a->capacity];
    a->count--;
    lp->count--;
    return item;
}

/**
 * Returns the first element in the list.
 *
 * @param lp the list to get the first element from
 * @return the first element
 * @timeComplexity O(1)
 */
void* getFirst(LIST* lp) {
    printf("getFirst\n");
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE* a = lp->head;
    while (a->count == 0) {
        a = a->next;
    }
    return a->data[lp->head->firstIndex];
}

/**
 * Returns the last element in the list.
 *
 * @param lp the list to get the last element from
 * @return the last element
 * @timeComplexity O(N)
 */
void* getLast(LIST* lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE* a = lp->head->prev;
    while (a->count == 0) {
        a = a->prev;
    }
    return a->data[(a->firstIndex + a->count - 1) % a->capacity];
}

/**
 * Returns the item at the given index.
 *
 * @param lp the list to access
 * @param index the index of access
 * @return the item at the given index
 * @timeComplexity O(N) where N is the given index
 */
void* getItem(LIST* lp, int index) {
    printf("getItem %i\n", index);
    assert(lp != NULL);
    assert(index >= 0 && index < lp->count);
    NODE* np = lp->head;
    printf("count: %u\n", lp->head->count);
    while (index >= np->count) {
        printf("next\n");
        index -= np->count;
        np = np->next;
    }
    printf("checking getitem: %i\n", (np->firstIndex + index) % np->capacity);
    return np->data[(np->firstIndex + index) % np->capacity];
}

/**
 * Sets the item at the given index to the given item.
 *
 * @param lp the list to modify
 * @param index the index to edit
 * @param item the new value of the item
 * @timeComplexity O(N) where N is the given index
 */
void setItem(LIST* lp, int index, void* item) {
    printf("setItem %i\n", index);
    assert(lp != NULL);
    assert(index >= 0 && index < lp->count);
    NODE* np = lp->head;
    while (index >= np->count) {
        index -= np->count;
        np = np->next;
    }
    np->data[(np->firstIndex + index) % np->capacity] = item;
}

int subNodes(LIST* lp) {
    int count = 0;
    NODE* a = lp->head;
    while (a != NULL) {
        count++;
        a = a->next;
    }
    return count;
}
/*

void debugPrint(LIST* a) {
    printf("debugPrint\n");
    printf("numItems: %d\n", numItems(a));
    printf("subNodes: %d\n", subNodes(a));
    printf("last: {%hu, %hu}\n", (*(COORD*) getLast(a)).x, (*(COORD*) getLast(a)).y);
    printf("first: {%hu, %hu}\n", (*(COORD*) getFirst(a)).x, (*(COORD*) getFirst(a)).y);
}*/