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
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i]->length == max) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'maxLists' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            maxLists[count++] = lists[i];
        }
    }
    *maxSize = count;
    return maxLists;
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
         *  dereference of possibly-NULL '*lists_65 + _8' [CWE-690] [-Wanalyzer-possible-null-dereference]
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
    int maxSize;
    List **maxLists = findMaxList(lists, size, &maxSize);
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