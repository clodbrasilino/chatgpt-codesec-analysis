#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int length;
    int *elements;
} List;

List** findMaxList(List **lists, int size, int *maxSize) {
    int max = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i]->length > max) {
            max = lists[i]->length;
        }
    }
    List **maxLists = malloc(sizeof(List*) * size);
    if (maxLists == NULL) return NULL;

    int count = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i]->length == max) {
            maxLists[count++] = lists[i];
        }
    }
    *maxSize = count;
    return maxLists;
}

int main() {
    int size = 3;
    List **lists = malloc(sizeof(List*) * size);
    if (lists == NULL) return 1;

    for(int i = 0; i < size; i++) {
        lists[i] = malloc(sizeof(List));
        if (lists[i] == NULL) return 1;

        lists[i]->length = i + 1;
        lists[i]->elements = malloc(sizeof(int) * (i + 1));
        if (lists[i]->elements == NULL) return 1;

        for(int j = 0; j <= i; j++) {
            lists[i]->elements[j] = j;
        }
    }
    int maxSize;
    List **maxLists = findMaxList(lists, size, &maxSize);
    if (maxLists == NULL) return 1;

    for(int i = 0; i < maxSize; i++) {
        for(int j = 0; j < maxLists[i]->length; j++) {
            printf("%d ", maxLists[i]->elements[j]);
        }
        printf("\n");
    }
    for(int i = 0; i < size; i++) {
        free(lists[i]->elements);
        free(lists[i]);
    }
    free(lists);
    free(maxLists);
    return 0;
}