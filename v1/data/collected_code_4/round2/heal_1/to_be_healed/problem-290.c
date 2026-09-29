#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int* array;
    int length;
} List;

List* findMaxList(List** listOfLists, int size) {
    int maxLength = 0;
    List* maxList = NULL;

    for(int i = 0; i < size; i++) {
        if(listOfLists[i] != NULL) {
            if(listOfLists[i]->length > maxLength) {
                maxLength = listOfLists[i]->length;
                maxList = listOfLists[i];
            }
        }
    }

    if(maxList == NULL) {
        printf("No valid list found\n");
        exit(EXIT_FAILURE);
    }

    return maxList;
}

int main() {
    int size = 3;
    List** listOfLists = (List**)malloc(sizeof(List*) * size);
    
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'listOfLists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        listOfLists[i] = (List*)malloc(sizeof(List));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*listOfLists_37 + _11' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        listOfLists[i]->array = (int*)malloc(sizeof(int) * (i+1));
        listOfLists[i]->length = i+1;
    }

    List* maxList = findMaxList(listOfLists, size);

    printf("Max list size: %d\n", maxList->length);

    for(int i = 0; i < size; i++) {
        free(listOfLists[i]->array);
        free(listOfLists[i]);
    }

    free(listOfLists);

    return 0;
}