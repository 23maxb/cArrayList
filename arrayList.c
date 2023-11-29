//filename: arrayList.c
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

    int (* compare)();
} LIST;

typedef struct node {
    void** data;
    unsigned firstIndex;
    unsigned count;
    struct node* next;
} NODE;

#define DEFAULT_SUBARRAY_LENGTH 10

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
    lp->head->next = NULL;
    lp->head->firstIndex = 0;
    lp->head->count = 0;
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
    NODE* np = lp->head;
    while (np != NULL) {
        NODE* next = np->next;
        free(np->data);
        free(np);
        np = next;
    }
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
    if (lp->head->count == DEFAULT_SUBARRAY_LENGTH) {
        NODE* np = malloc(sizeof(NODE));
        assert(np != NULL);
        np->data = malloc(DEFAULT_SUBARRAY_LENGTH * sizeof(void*));
        assert(np->data != NULL);
        np->next = lp->head;
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
    printf("item: %u\n", *((unsigned*) item));
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
    assert(lp != NULL);
    assert(item != NULL);
    NODE* last = lp->head;
    while (last->next != NULL) {
        last = last->next;
    }
    if (last->count == DEFAULT_SUBARRAY_LENGTH) {
        NODE* np = malloc(sizeof(NODE));
        assert(np != NULL);
        np->data = malloc(DEFAULT_SUBARRAY_LENGTH * sizeof(void*));
        assert(np->data != NULL);
        np->next = NULL;
        np->firstIndex = 0;
        np->count = 0;
        last->next = np;
        last = np;
    }
    last->data[last->firstIndex + last->count] = item;
    last->count++;
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
    assert(lp != NULL);
    assert(lp->count > 0);
    void* item = lp->head->data[lp->head->firstIndex];
    lp->head->firstIndex++;
    lp->head->count--;
    lp->count--;
    if (lp->head->count == 0 && lp->head->next != NULL) {
        NODE* np = lp->head;
        lp->head = lp->head->next;
        free(np->data);
        free(np);
    }
    return item;
}

void* removeLast(LIST* lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE* a = lp->head;
    while (a->next != NULL && a->next->count > 0) {
        a = a->next;
    }
    void* item = a->data[a->firstIndex + a->count - 1];
    a->count--;
    lp->count--;
    return item;
}

void* getFirst(LIST* lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    return lp->head->data[lp->head->firstIndex];
}

void* getLast(LIST* lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE* a = lp->head;
    while (a->next != NULL && a->next->count > 0) {
        a = a->next;
    }
    return a->data[a->firstIndex + a->count - 1];
}

void* getItem(LIST* lp, int index) {
    assert(lp != NULL);
    assert(index >= 0 && index < lp->count);
    NODE* np = lp->head;
    while (index >= np->count) {
        index -= np->count;
        np = np->next;
    }
    return np->data[np->firstIndex + index];
}

void setItem(LIST* lp, int index, void* item) {
    assert(lp != NULL);
    assert(index >= 0 && index < lp->count);
    NODE* np = lp->head;
    while (index >= np->count) {
        index -= np->count;
        np = np->next;
    }
    np->data[np->firstIndex + index] = item;
}
