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

    firstList->data = 5;
    firstList->next = NULL;

    secondList->data = 10;
    secondList->next = NULL;

    List *listOfLists[3] = {firstList, secondList, NULL};

    printf("Count of the Square: %d\n", countAndSquare(listOfLists));

    free(firstList);
    free(secondList);

    return 0;
}
