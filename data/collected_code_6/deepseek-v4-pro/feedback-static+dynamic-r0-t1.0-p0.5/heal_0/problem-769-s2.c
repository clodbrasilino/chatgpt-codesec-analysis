#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

int contains(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node* listDifference(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* current = list1;
    
    while (current != NULL) {
        if (!contains(list2, current->data) && !contains(result, current->data)) {
            appendNode(&result, current->data);
        }
        current = current->next;
    }
    
    return result;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void printList(Node* head) {
    Node* current = head;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* difference = NULL;
    
    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);
    appendNode(&list1, 4);
    appendNode(&list1, 5);
    
    appendNode(&list2, 2);
    appendNode(&list2, 4);
    appendNode(&list2, 6);
    
    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);
    
    difference = listDifference(list1, list2);
    printf("Difference (List1 - List2): ");
    printList(difference);
    
    freeList(list1);
    freeList(list2);
    freeList(difference);
    
    return 0;
}