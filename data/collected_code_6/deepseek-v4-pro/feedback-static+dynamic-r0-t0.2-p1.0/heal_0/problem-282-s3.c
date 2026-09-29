#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    
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

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node* subtractLists(Node* list1, Node* list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    Node* result = NULL;
    Node* current1 = list1;
    Node* current2 = list2;
    
    while (current1 != NULL && current2 != NULL) {
        appendNode(&result, current1->data - current2->data);
        current1 = current1->next;
        current2 = current2->next;
    }
    
    while (current1 != NULL) {
        appendNode(&result, current1->data);
        current1 = current1->next;
    }
    
    while (current2 != NULL) {
        appendNode(&result, -current2->data);
        current2 = current2->next;
    }
    
    return result;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;
    
    appendNode(&list1, 10);
    appendNode(&list1, 20);
    appendNode(&list1, 30);
    appendNode(&list1, 40);
    
    appendNode(&list2, 5);
    appendNode(&list2, 15);
    appendNode(&list2, 25);
    
    printf("List 1: ");
    printList(list1);
    
    printf("List 2: ");
    printList(list2);
    
    result = subtractLists(list1, list2);
    
    printf("Result: ");
    printList(result);
    
    freeList(list1);
    freeList(list2);
    freeList(result);
    
    return 0;
}