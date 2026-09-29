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

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* multiplyLists(Node* list1, Node* list2) {
    if (!list1 || !list2) return NULL;

    Node* resultList = NULL;
    Node* curr1 = list1;
    Node* curr2 = list2;

    while (curr1 && curr2) {
        append(&resultList, curr1->data * curr2->data);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return resultList;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    append(&list1, 2);
    append(&list1, 4);
    append(&list1, 6);

    append(&list2, 3);
    append(&list2, 5);
    append(&list2, 7);

    result = multiplyLists(list1, list2);

    printList(result);

    freeList(list1);
    freeList(list2);
    freeList(result);

    return EXIT_SUCCESS;
}