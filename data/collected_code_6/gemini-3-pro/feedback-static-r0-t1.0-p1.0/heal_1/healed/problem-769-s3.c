#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

bool contains(Node* head, int data) {
    Node* current = head;
    while (current) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* getDifference(Node* list1, Node* list2) {
    Node* diffList = NULL;
    Node* current = list1;

    while (current) {
        if (!contains(list2, current->data) && !contains(diffList, current->data)) {
            append(&diffList, current->data);
        }
        current = current->next;
    }

    return diffList;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* diff = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);
    append(&list1, 4);
    append(&list1, 5);

    append(&list2, 3);
    append(&list2, 4);
    append(&list2, 6);

    diff = getDifference(list1, list2);

    printList(diff);

    freeList(list1);
    freeList(list2);
    freeList(diff);

    return 0;
}