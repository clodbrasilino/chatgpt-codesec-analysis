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
    if (!head) {
        return;
    }
    
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node* addLists(Node* list1, Node* list2) {
    Node* resultList = NULL;
    
    while (list1 != NULL && list2 != NULL) {
        append(&resultList, list1->data + list2->data);
        list1 = list1->next;
        list2 = list2->next;
    }
    
    while (list1 != NULL) {
        append(&resultList, list1->data);
        list1 = list1->next;
    }
    
    while (list2 != NULL) {
        append(&resultList, list2->data);
        list2 = list2->next;
    }
    
    return resultList;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* resultList = NULL;
    
    append(&list1, 3);
    append(&list1, 5);
    append(&list1, 7);
    
    append(&list2, 2);
    append(&list2, 4);
    append(&list2, 6);
    append(&list2, 8);
    
    resultList = addLists(list1, list2);
    
    printList(resultList);
    
    freeList(list1);
    freeList(list2);
    freeList(resultList);
    
    return EXIT_SUCCESS;
}