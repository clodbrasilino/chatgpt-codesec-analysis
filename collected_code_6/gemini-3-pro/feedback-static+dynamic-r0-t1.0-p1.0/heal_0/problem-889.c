#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct ListOfLists {
    struct Node* head;
    struct ListOfLists* next;
};

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

void reverseListOfLists(struct ListOfLists* lolHead) {
    if (lolHead == NULL) {
        return;
    }
    
    struct ListOfLists* current = lolHead;
    while (current != NULL) {
        current->head = reverseList(current->head);
        current = current->next;
    }
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct ListOfLists* createListOfListsNode(struct Node* head) {
    struct ListOfLists* newNode = (struct ListOfLists*)malloc(sizeof(struct ListOfLists));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->head = head;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void printListOfLists(struct ListOfLists* lolHead) {
    struct ListOfLists* current = lolHead;
    int index = 0;
    while (current != NULL) {
        printf("List %d: ", index++);
        printList(current->head);
        current = current->next;
    }
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

void freeListOfLists(struct ListOfLists* lolHead) {
    struct ListOfLists* current = lolHead;
    struct ListOfLists* next = NULL;
    while (current != NULL) {
        next = current->next;
        freeList(current->head);
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node* l1 = createNode(1);
    l1->next = createNode(2);
    l1->next->next = createNode(3);
    
    struct Node* l2 = createNode(4);
    l2->next = createNode(5);
    
    struct Node* l3 = createNode(6);
    l3->next = createNode(7);
    l3->next->next = createNode(8);
    l3->next->next->next = createNode(9);
    
    struct ListOfLists* lol = createListOfListsNode(l1);
    lol->next = createListOfListsNode(l2);
    lol->next->next = createListOfListsNode(l3);
    
    reverseListOfLists(lol);
    
    printListOfLists(lol);
    
    freeListOfLists(lol);
    
    return 0;
}