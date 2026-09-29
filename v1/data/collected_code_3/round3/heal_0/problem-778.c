#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (*head == NULL) {
        *head = createNode(data);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = createNode(data);
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void packDuplicates(Node* head) {
    while (head != NULL && head->next != NULL) {
        if (head->data == head->next->data) {
            printf("[ ");
            while (head != NULL && head->next != NULL && head->data == head->next->data) {
                printf("%d ", head->data);
                head = head->next;
            }
            printf("%d ] ", head->data);
        } else {
            printf("[ %d ] ", head->data);
        }
        head = head->next;
    }
    if (head != NULL) {
        printf("[ %d ]\n", head->data);
    } else {
        printf("\n");
    }
}

int main() {
    Node* head = NULL;
    appendNode(&head, 1);
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 4);
    appendNode(&head, 4);
    appendNode(&head, 5);

    printf("Original List: ");
    printList(head);

    printf("Packed List: ");
    packDuplicates(head);

    return 0;
}