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
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

struct Node* moduloLists(struct Node* list1, struct Node* list2) {
    struct Node* resultHead = NULL;
    struct Node* temp1 = list1;
    struct Node* temp2 = list2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp2->data == 0) {
            freeList(resultHead);
            return NULL;
        }
        appendNode(&resultHead, temp1->data % temp2->data);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return resultHead;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* result = NULL;

    appendNode(&list1, 10);
    appendNode(&list1, 20);
    appendNode(&list1, 30);

    appendNode(&list2, 3);
    appendNode(&list2, 7);
    appendNode(&list2, 4);

    result = moduloLists(list1, list2);

    if (result != NULL) {
        printList(result);
        freeList(result);
    } else {
        printf("Error: Division by zero or lists of unequal length processed up to shortest.\n");
    }

    freeList(list1);
    freeList(list2);

    return 0;
}