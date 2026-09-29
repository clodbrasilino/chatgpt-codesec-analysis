#include <stdio.h>
#include <stdlib.h>

struct listNode {
    struct listNode *next;
};

struct listOfLists {
    struct listNode * node;
    struct listOfLists *next;
};

int squareListsCount(struct listOfLists *lists) {
    struct listOfLists *temp = lists;
    int count = 0;
    
    while (temp) {
        count++;
        temp = temp->next;
    }

    return count * count;
}

int main(void) {
    struct listOfLists *list = malloc(sizeof(struct listOfLists));
    if(list == NULL) {
        return -1;
    }
    list->next = malloc(sizeof(struct listOfLists));
    if(list->next == NULL) {
        free(list);
        return -1;
    }
    list->next->next = malloc(sizeof(struct listOfLists));
    if(list->next->next == NULL) {
        free(list->next);
        free(list);
        return -1;
    }
    list->next->next->next = NULL;

    printf("Squared count of lists: %d\n", squareListsCount(list));

    free(list->next->next);
    free(list->next);
    free(list);

    return 0;
}
