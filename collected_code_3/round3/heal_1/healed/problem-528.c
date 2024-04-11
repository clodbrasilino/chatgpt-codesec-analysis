#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int length;
    int *elements;
} List;

List** findMinLengthLists(List **lists, int numLists, int *numMinLists) {
    int minLength = lists[0]->length;
    for(int i = 1; i < numLists; i++) {
        if(lists[i]->length < minLength) {
            minLength = lists[i]->length;
        }
    }

    List **minLengthLists = (List **) malloc(numLists * sizeof(List *));
    if (minLengthLists == NULL) return NULL;

    *numMinLists = 0;
    for(int i = 0; i < numLists; i++) {
        if(lists[i]->length == minLength) {
            minLengthLists[*numMinLists] = lists[i];
            (*numMinLists)++;
        }
    }

    return minLengthLists;
}

int main() {
    int numLists = 3;
    List **lists = (List **) malloc(numLists * sizeof(List *));
    if (lists == NULL) return 1;

    for(int i = 0; i < numLists; i++) {
        lists[i] = (List *) malloc(sizeof(List));
        if (lists[i] == NULL) return 1;

        lists[i]->length = i + 1;
        lists[i]->elements = (int *) malloc(lists[i]->length * sizeof(int));
        if (lists[i]->elements == NULL) return 1;

        for(int j = 0; j < lists[i]->length; j++) {
            lists[i]->elements[j] = j;
        }
    }

    int numMinLists;
    List **minLengthLists = findMinLengthLists(lists, numLists, &numMinLists);
    if (minLengthLists == NULL) return 1;

    for(int i = 0; i < numMinLists; i++) {
        for(int j = 0; j < minLengthLists[i]->length; j++) {
            printf("%d ", minLengthLists[i]->elements[j]);
        }
        printf("\n");
    }

    for(int i = 0; i < numLists; i++) {
        free(lists[i]->elements);
        free(lists[i]);
    }
    free(lists);
    free(minLengthLists);

    return 0;
}