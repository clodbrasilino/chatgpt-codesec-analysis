#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *keys;
    int *values;
    int size;
    int capacity;
} Dictionary;

typedef struct {
    Dictionary *items;
    int size;
    int capacity;
} List;

int all_dicts_empty(const List *list) {
    if (list == NULL) {
        return 1;
    }

    for (int i = 0; i < list->size; i++) {
        if (list->items[i].size > 0) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    Dictionary d1 = {NULL, NULL, 0, 0};
    Dictionary d2 = {NULL, NULL, 0, 0};
    
    int k = 1;
    int v = 1;
    Dictionary d3 = {&k, &v, 1, 1};

    List l1 = {&d1, 2, 2};
    l1.items[0] = d1;
    l1.items[1] = d2;

    List l2 = {&d3, 1, 1};
    l2.items[0] = d3;

    List l3 = {NULL, 0, 0};

    int r1 = all_dicts_empty(&l1);
    int r2 = all_dicts_empty(&l2);
    int r3 = all_dicts_empty(&l3);
    int r4 = all_dicts_empty(NULL);

    printf("%d %d %d %d\n", r1, r2, r3, r4);

    return 0;
}