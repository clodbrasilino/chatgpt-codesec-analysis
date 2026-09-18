#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int data;
    struct List *next;
} List;

int countAndSquare(List **listOfLists) {
    int count = 0;
    if(listOfLists) {
        while(*listOfLists) {
            count++;
            listOfLists++;
        }
    }
    return count*count;
}

int main() {
    List *firstList = (List*) malloc(sizeof(List));
    List *secondList = (List*) malloc(sizeof(List));

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'firstList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    firstList->data = 5;
    firstList->next = NULL;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'secondList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    secondList->data = 10;
    secondList->next = NULL;

    List *listOfLists[3] = {firstList, secondList, NULL};

    printf("Count of the Square: %d\n", countAndSquare(listOfLists));

    free(firstList);
    free(secondList);

    return 0;
}
