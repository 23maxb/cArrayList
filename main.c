#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "stdbool.h"
#include <stdio.h>
#include "ArrayList.c"


static int intcmp(int* i1, int* i2) {
    assert(i1 != NULL);
    assert(i2 != NULL);
    return (*i1 < *i2) ? -1 : (*i1 > *i2);
}

int main(void) {
    LIST* a = createList();
    unsigned i = 0;
    unsigned* j;
    for (; i < 20; i++) {
        j = malloc(sizeof(int));
        *j = i;
        addLast(a, j);
    }
    j = malloc(sizeof(int));
    i = 99;
    *j = i;
    printf("hello: %u", *((unsigned*) getItem(a, 5)));
    setItem(a, 5, j);
    printf("first: %u\n", *((unsigned*) getFirst(a)));
    for (i = 0; i < numItems(a); i++) {
        printf("index %u: %u\n", i, *((unsigned*) getItem(a, i)));
    }
    printf("removing last");
    free(removeLast(a));
    for (i = 0; i < numItems(a); i++) {
        printf("index %u: %u\n", i, *((unsigned*) getItem(a, i)));
    }
    printf("removing all");
    while (numItems(a) > 1) {
        removeFirst(a);
    }
    for (i = 0; i < numItems(a); i++) {
        printf("index %u: %u\n", i, *((unsigned*) getItem(a, i)));
    }
    destroyList(a);
    exit(EXIT_SUCCESS);
}