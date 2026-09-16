#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct List {
    int size;
    ListNode *head;
    ListNode *tail;
} List;

ListNode* createNode(int value) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    node->value = value;
    node->next = NULL;
    return node;
}

List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void appendToList(List *list, int value) {
    ListNode *newNode = createNode(value);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void freeList(List *list) {
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

List* filterSublists(List *lists, int min, int max) {
    List *filteredLists = createList();
    ListNode *current = lists->head;
    while (current != NULL) {
        List *sublist = (List*)current->value;
        const ListNode *subCurrent = sublist->head;
        if (subCurrent != NULL && subCurrent->value >= min && subCurrent->value <= max) {
            appendToList(filteredLists, (int)sublist);
        }
        current = current->next;
    }
    return filteredLists;
}

int main() {
    List *lists = createList();
    List *sublist1 = createList();
    appendToList(sublist1, 5);
    appendToList(sublist1, 7);
    appendToList(sublist1, 10);

    List *sublist2 = createList();
    appendToList(sublist2, 1);
    appendToList(sublist2, 3);

    List *sublist3 = createList();
    appendToList(sublist3, 8);
    appendToList(sublist3, 11);

    appendToList(lists, (int)sublist1);
    appendToList(lists, (int)sublist2);
    appendToList(lists, (int)sublist3);

    int min = 4;
    int max = 9;
    List *filteredLists = filterSublists(lists, min, max);

    ListNode *current = filteredLists->head;
    while (current != NULL) {
        List *sublist = (List*)current->value;
        const ListNode *subCurrent = sublist->head;
        while (subCurrent != NULL) {
            printf("%d ", subCurrent->value);
            subCurrent = subCurrent->next;
        }
        printf("\n");
        current = current->next;
    }

    freeList(filteredLists);
    freeList(lists);

    return 0;
}