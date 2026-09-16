#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List {
    int value;
    struct List *next;
} List;

bool isSubset(List *big, List *small) {
    if (small == NULL) return true;
    if (big == NULL && small != NULL) return false;
    if (big->value == small->value) {
        return isSubset(big->next, small->next);
    }
    return isSubset(big->next, small);
}

List* createNode(int value) {
    List *newNode = (List *)malloc(sizeof(List));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void freeList(List *list) {
    while (list != NULL) {
        List *temp = list;
        list = list->next;
        free(temp);
    }
}

int main() {
    List *bigList = createNode(1);
    bigList->next = createNode(2);
    bigList->next->next = createNode(3);
    bigList->next->next->next = createNode(4);

    List *smallList1 = createNode(2);
    smallList1->next = createNode(3);

    List *smallList2 = createNode(2);
    smallList2->next = createNode(5);

    if (isSubset(bigList, smallList1)) {
        printf("smallList1 is a subset of bigList\n");
    } else {
        printf("smallList1 is not a subset of bigList\n");
    }

    if (isSubset(bigList, smallList2)) {
        printf("smallList2 is a subset of bigList\n");
    } else {
        printf("smallList2 is not a subset of bigList\n");
    }

    freeList(bigList);
    freeList(smallList1);
    freeList(smallList2);

    return 0;
}