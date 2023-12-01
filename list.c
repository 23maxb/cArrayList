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
 * Makes a new node with the given capacity and next and previous nodes.
 * @param capacity the capacity of the new node
 * @param next the value you want to be next (can be null)
 * @param prev the value you want to be previous (can be null)
 * @return the new node
 * @tiemComplexity O(1)
 */
NODE* makeNode(unsigned capacity, NODE* next, NODE* prev) {
    NODE* np = malloc(sizeof(NODE));
    assert(np != NULL);
    np->data = malloc(capacity * sizeof(void*));
    assert(np->data != NULL);
    np->capacity = capacity;
    np->next = next;
    np->prev = prev;
    np->firstIndex = 0;
    np->count = 0;
    return np;
}

/**
 * Creates a new list and returns a pointer to it. Defualt length is 3 * DEFAULT_SUBARRAY_LENGTH (6)
 *
 * @return the new list
 * @timeComplexity O(1)
 */
LIST* createList() {
    LIST* lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = makeNode(DEFAULT_SUBARRAY_LENGTH, NULL, NULL);
    lp->head->next = makeNode(DEFAULT_SUBARRAY_LENGTH * 2, lp->head, lp->head);
    lp->head->prev = lp->head->next;
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
    NODE* current = lp->head;
    do {
        NODE* next = current->next;
        free(current->data);
        free(current);
        current = next;
    } while (current != lp->head);
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
    if (lp->head->capacity == lp->head->count) {
        NODE* np = makeNode(lp->head->capacity * 2, lp->head, lp->head->prev);
        lp->head->prev->next = np;
        lp->head->prev = np;
        lp->head = np;
    }
    if (lp->head->firstIndex == 0)
        lp->head->firstIndex += lp->head->capacity;
    lp->head->firstIndex = (lp->head->firstIndex - 1) % lp->head->capacity;
    lp->head->count++;
    lp->head->data[lp->head->firstIndex] = item;
    lp->count++;
}

/**
 * Adds an item to the end of the list.
 *
 * @param lp the list to add the item to
 * @param item the item to add (cant be null)
 * @timeComplexity O(1)
 */
void addLast(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(item != NULL);
    NODE* lastNode = lp->head->prev;
    if (lastNode->count == lastNode->capacity) {
        NODE* newNode = makeNode(lastNode->capacity * 2, lp->head, lastNode);
        lastNode->next = newNode;
        lp->head->prev = newNode;
        lastNode = newNode;
    }
    unsigned insertIndex = (lastNode->firstIndex + lastNode->count) % lastNode->capacity;
    lastNode->data[insertIndex] = item;
    lastNode->count++;
    lp->count++;
}


/**
 * Removes the item at the front of the list.
 *
 * @param lp the list to add the item to
 * @param item the item to add (cant be null)
 * @timeComplexity O(1) usually; O(log(N)) where N is the number of elements removed from the front of the array worst case
 */
void* removeFirst(LIST* lp) {
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
 * @timeComplexity O(1) usually; O(log(N)) where N is the number of elements removed from the end of the array worst case
 */
void* removeLast(LIST* lp) {
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
 * @timeComplexity O(1) usually; O(log(N)) where N is the number of elements removed from the front of the array worst case
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
 * @timeComplexity O(1) usually; O(log(N)) where N is the number of elements removed from the end of the array worst case
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
    assert(lp != NULL);
    assert(index >= 0 && index < lp->count);
    NODE* np = lp->head;
    while (index >= np->count) {
        index -= np->count;
        np = np->next;
    }
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
    assert(lp != NULL);
    assert(index >= 0 && index < lp->count);
    NODE* np = lp->head;
    while (index >= np->count) {
        index -= np->count;
        np = np->next;
    }
    np->data[(np->firstIndex + index) % np->capacity] = item;
}


/*

void debugPrint(LIST* a) {
    printf("debugPrint\n");
    printf("numItems: %d\n", numItems(a));
    printf("subNodes: %d\n", subNodes(a));
    printf("last: {%hu, %hu}\n", (*(COORD*) getLast(a)).x, (*(COORD*) getLast(a)).y);
    printf("first: {%hu, %hu}\n", (*(COORD*) getFirst(a)).x, (*(COORD*) getFirst(a)).y);
}*/