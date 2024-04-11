#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int length;
    int *elements;
} List;


List** findMinLengthLists(List **lists, int size, int *resultSize) {
    int min = lists[0]->length;
    for(int i = 1; i < size; i++) {
        if(lists[i]->length < min) {
            min = lists[i]->length;
        }
    }

    List **result = malloc(sizeof(List*) * size);
    if (!result) return NULL; 

    *resultSize = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i]->length == min) {
            result[(*resultSize)++] = lists[i];
        }
    }

    return result;
}


int main() {
    int size = 3;
    List **lists = malloc(sizeof(List*) * size); 

    if (!lists) return -1;

    for(int i = 0; i < size; i++) {
        lists[i] = malloc(sizeof(List));
        if(!lists[i]) return -1;

        lists[i]->length = i + 1;
        lists[i]->elements = malloc(sizeof(int) * (i + 1));

        if(!lists[i]->elements) return -1;
        
        for(int j = 0; j <= i; j++) {
            lists[i]->elements[j] = j;
        }
    }

    int resultSize;
    List **minLengthLists = findMinLengthLists(lists, size, &resultSize);

    if (!minLengthLists) return -1;

    for(int i = 0; i < resultSize; i++) {
        printf("List %d has length %d\n", i, minLengthLists[i]->length);
    }

    for(int i = 0; i < size; i++) {
        free(lists[i]->elements);
        free(lists[i]);
    }
    free(lists);
    free(minLengthLists);

    return 0;
}