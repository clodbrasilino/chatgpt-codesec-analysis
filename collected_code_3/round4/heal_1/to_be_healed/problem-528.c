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
    *resultSize = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i]->length == min) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[(*resultSize)++] = lists[i];
        }
    }

    return result;
}

int main() {
    int size = 3;
    List **lists = malloc(sizeof(List*) * size);

    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i] = malloc(sizeof(List));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*lists_54 + _8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i]->length = i + 1;
        lists[i]->elements = malloc(sizeof(int) * (i + 1));
        for(int j = 0; j <= i; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '**_22.elements + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            lists[i]->elements[j] = j;
        }
    }

    int resultSize;
    List **minLengthLists = findMinLengthLists(lists, size, &resultSize);

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