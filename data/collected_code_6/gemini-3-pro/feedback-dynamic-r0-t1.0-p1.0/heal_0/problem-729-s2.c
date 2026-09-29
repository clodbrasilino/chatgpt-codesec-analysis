#include <stdio.h>
#include <stdlib.h>

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
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node* addLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node** tail = &result;
    
    while (list1 || list2) {
        int sum = 0;
        if (list1) {
            sum += list1->data;
            list1 = list1->next;
        }
        if (list2) {
            sum += list2->data;
            list2 = list2->next;
        }
        
        *tail = createNode(sum);
        tail = &((*tail)->next);
    }
    
    return result;
}

void printList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    
    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);
    
    append(&list2, 4);
    append(&list2, 5);
    append(&list2, 6);
    append(&list2, 7);
    
    Node* result = addLists(list1, list2);
    
    printList(result);
    
    freeList(list1);
    freeList(list2);
    freeList(result);
    
    return EXIT_SUCCESS;
}