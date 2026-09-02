#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
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

struct Node* alternateElements(struct Node* head) {
    struct Node* newHead = NULL;
    int isEven = 1;
    while (head != NULL) {
        if (isEven % 2 == 1) {
            insertAtEnd(&newHead, head->data);
        }
        head = head->next;
        isEven++;
    }
    return newHead;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* list = NULL;
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 2);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);
    insertAtEnd(&list, 5);

    printf("Original List: ");
    printList(list);

    struct Node* alternateList = alternateElements(list);

    printf("Alternate Elements: ");
    printList(alternateList);

    return 0;
}