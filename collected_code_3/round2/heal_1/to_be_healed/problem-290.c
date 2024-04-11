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
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'maxLists' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            maxLists[(*maxListsCount)++] = lists[i];
        }
    }

    return maxLists;
}

int main() {
    int n = 3;
    List **lists = malloc(n * sizeof(List *));
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i] = malloc(sizeof(List));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*lists_74 + _8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i]->length = i + 1;
        lists[i]->elements = malloc(lists[i]->length * sizeof(int));
        for (int j = 0; j < lists[i]->length; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '**_26.elements + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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