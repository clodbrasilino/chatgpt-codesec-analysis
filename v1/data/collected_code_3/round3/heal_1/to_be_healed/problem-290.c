#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int data;
    struct List *next;
} List;

typedef struct ListOfLists {
    List *list;
    struct ListOfLists *next;
} ListOfLists;

List* createList(int data) {
    List *newList = (List*)malloc(sizeof(List));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newList->data = data;
    newList->next = NULL;
    return newList;
}

ListOfLists* createListOfLists(List *list) {
    ListOfLists *newListOfLists = (ListOfLists*)malloc(sizeof(ListOfLists));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newListOfLists' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newListOfLists->list = list;
    newListOfLists->next = NULL;
    return newListOfLists;
}

int getListLength(List *list) {
    int length = 0;
    while(list != NULL) {
        length++;
        list = list->next;
    }
    return length;
}

ListOfLists* findMaxList(ListOfLists *lists) {
    if(lists == NULL) {
        return NULL;
    }
    ListOfLists *maxList = lists;
    int maxLength = getListLength(lists->list);
    lists = lists->next;
    while(lists != NULL) {
        int length = getListLength(lists->list);
        if(length > maxLength) {
            maxLength = length;
            maxList = lists;
        }
        lists = lists->next;
    }
    return maxList;
}

int main() {
    List *list1 = createList(1);
    list1->next = createList(2);
    list1->next->next = createList(3);

    List *list2 = createList(4);
    list2->next = createList(5);

    ListOfLists *lists = createListOfLists(list1);
    lists->next = createListOfLists(list2);

    ListOfLists *maxList = findMaxList(lists);
    printf("The list with maximum length is: ");
    while(maxList->list != NULL) {
        printf("%d ", maxList->list->data);
        maxList->list = maxList->list->next;
    }
    printf("\n");

    return 0;
}