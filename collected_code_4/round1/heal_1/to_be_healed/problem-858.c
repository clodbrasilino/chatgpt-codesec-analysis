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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->next = malloc(sizeof(struct listOfLists));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->next->next = malloc(sizeof(struct listOfLists));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list_12->next.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->next->next->next = NULL;

    printf("Squared count of lists: %d\n", squareListsCount(list));

    free(list->next->next);
    free(list->next);
    free(list);

    return 0;
}