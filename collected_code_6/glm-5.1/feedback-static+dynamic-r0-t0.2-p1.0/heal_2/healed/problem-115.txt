#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *keys;
    int *values;
    int size;
    int capacity;
} Dictionary;

typedef struct {
    Dictionary *dicts;
    int count;
} DictList;

int are_all_empty(DictList *list) {
    if (list == NULL) {
        return 1;
    }
    for (int i = 0; i < list->count; i++) {
        if (list->dicts[i].size > 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    Dictionary d1 = {NULL, NULL, 0, 0};
    Dictionary d2 = {NULL, NULL, 0, 0};
    Dictionary d3 = {(int *)malloc(sizeof(int)), (int *)malloc(sizeof(int)), 1, 1};
    
    if (d3.keys == NULL || d3.values == NULL) {
        free(d3.keys);
        free(d3.values);
        return 1;
    }

    d3.keys[0] = 1;
    d3.values[0] = 100;
    d3.capacity = 1;

    DictList list1 = {(Dictionary[]){d1, d2}, 2};
    DictList list2 = {(Dictionary[]){d1, d3}, 2};

    int result1 = are_all_empty(&list1);
    int result2 = are_all_empty(&list2);

    printf("%d\n", result1);
    printf("%d\n", result2);

    free(d3.keys);
    free(d3.values);

    return 0;
}