#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int length;
    int *elements;
} List;

List **findMaxLists(List **lists, int n, int *maxListsCount) {
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        if (lists[i]->length > maxLength) {
            maxLength = lists[i]->length;
        }
    }

    List **maxLists = malloc(n * sizeof(List *));
    *maxListsCount = 0;
    for (int i = 0; i < n; i++) {
        if (lists[i]->length == maxLength) {
            maxLists[(*maxListsCount)++] = lists[i];
        }
    }

    return maxLists;
}

int main() {
    int n = 3;
    List **lists = malloc(n * sizeof(List *));
    for (int i = 0; i < n; i++) {
        lists[i] = malloc(sizeof(List));
        lists[i]->length = i + 1;
        lists[i]->elements = malloc(lists[i]->length * sizeof(int));
        for (int j = 0; j < lists[i]->length; j++) {
            lists[i]->elements[j] = j;
        }
    }

    int maxListsCount;
    List **maxLists = findMaxLists(lists, n, &maxListsCount);

    for (int i = 0; i < maxListsCount; i++) {
        for (int j = 0; j < maxLists[i]->length; j++) {
            printf("%d ", maxLists[i]->elements[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(lists[i]->elements);
        free(lists[i]);
    }
    free(lists);
    free(maxLists);

    return 0;
}