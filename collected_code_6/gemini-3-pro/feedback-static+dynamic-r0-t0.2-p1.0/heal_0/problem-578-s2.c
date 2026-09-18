#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    if (head == NULL) {
        return;
    }
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

struct Node* interleaveLists(struct Node* list1, struct Node* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    struct Node* head = list1;
    struct Node* current1 = list1;
    struct Node* current2 = list2;
    struct Node* next1 = NULL;
    struct Node* next2 = NULL;

    while (current1 != NULL && current2 != NULL) {
        next1 = current1->next;
        next2 = current2->next;

        current1->next = current2;
        if (next1 != NULL) {
            current2->next = next1;
        }

        current1 = next1;
        current2 = next2;
    }

    return head;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 3);
    appendNode(&list1, 5);

    appendNode(&list2, 2);
    appendNode(&list2, 4);
    appendNode(&list2, 6);

    struct Node* interleavedList = interleaveLists(list1, list2);

    printList(interleavedList);

    freeList(interleavedList);

    return EXIT_SUCCESS;
}