#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int length;
    int *elements;
} List;

List** findMinLengthLists(List **lists, int numLists, int *minListCount) {
    int minLength = lists[0]->length;
    for(int i = 1; i < numLists; i++) {
        if(lists[i]->length < minLength) {
            minLength = lists[i]->length;
        }
    }

    List **minLengthLists = malloc(sizeof(List*) * numLists);
    *minListCount = 0;
    for(int i = 0; i < numLists; i++) {
        if(lists[i]->length == minLength) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'minLengthLists' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            minLengthLists[*minListCount] = lists[i];
            (*minListCount)++;
        }
    }

    return minLengthLists;
}

int main() {
    int numLists = 3;
    List **lists = malloc(sizeof(List*) * numLists);

    for(int i = 0; i < numLists; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i] = malloc(sizeof(List));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*lists_75 + _8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i]->length = i + 1;
        lists[i]->elements = malloc(sizeof(int) * lists[i]->length);
        for(int j = 0; j < lists[i]->length; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '**_26.elements + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            lists[i]->elements[j] = j;
        }
    }

    int minListCount;
    List **minLengthLists = findMinLengthLists(lists, numLists, &minListCount);

    printf("Lists with minimum length:\n");
    for(int i = 0; i < minListCount; i++) {
        printf("List %d: ", i + 1);
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