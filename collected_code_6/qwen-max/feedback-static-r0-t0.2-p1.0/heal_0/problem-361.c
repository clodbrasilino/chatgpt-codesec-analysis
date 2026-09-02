#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int* data;
    int size;
    struct List* next;
} List;

List* createList(int size) {
    List* newList = (List*)malloc(sizeof(List));
    if (newList == NULL) exit(EXIT_FAILURE);
    newList->data = (int*)malloc(size * sizeof(int));
    if (newList->data == NULL) {
        free(newList);
        exit(EXIT_FAILURE);
    }
    newList->size = size;
    newList->next = NULL;
    return newList;
}

void appendToList(List** head, List* newList) {
    if (*head == NULL) {
        *head = newList;
    } else {
        List* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newList;
    }
}

List* removeEmptyLists(List* head) {
    List* dummy = (List*)malloc(sizeof(List));
    if (dummy == NULL) exit(EXIT_FAILURE);
    dummy->next = head;
    List* prev = dummy;
    List* current = head;

    while (current != NULL) {
        if (current->size == 0) {
            prev->next = current->next;
            free(current->data);
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    List* newHead = dummy->next;
    free(dummy);
    return newHead;
}

void printList(List* head) {
    while (head != NULL) {
        for (int i = 0; i < head->size; ++i) {
            printf("%d ", head->data[i]);
        }
        printf("\n");
        head = head->next;
    }
}

int main() {
    List* head = NULL;

    List* list1 = createList(3);
    list1->data[0] = 1;
    list1->data[1] = 2;
    list1->data[2] = 3;
    appendToList(&head, list1);

    List* list2 = createList(0);
    appendToList(&head, list2);

    List* list3 = createList(2);
    list3->data[0] = 4;
    list3->data[1] = 5;
    appendToList(&head, list3);

    List* list4 = createList(0);
    appendToList(&head, list4);

    head = removeEmptyLists(head);

    printList(head);

    while (head != NULL) {
        List* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}