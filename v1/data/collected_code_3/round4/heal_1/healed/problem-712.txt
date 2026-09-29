#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
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

void removeDuplicates(Node* head) {
    Node *ptr1, *ptr2, *dup;
    ptr1 = head;

    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;

        while (ptr2->next != NULL) {
            if (ptr1->data == ptr2->next->data) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            } else {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* head = createNode(10);
    if(head == NULL) return 1;

    Node* second = createNode(12);
    if(second == NULL) return 1;
    head->next = second;

    Node* third = createNode(11);
    if(third == NULL) return 1;
    second->next = third;

    Node* forth = createNode(11);
    if(forth == NULL) return 1;
    third->next = forth;

    Node* fifth = createNode(12);
    if(fifth == NULL) return 1;
    forth->next = fifth;

    Node* sixth = createNode(11);
    if(sixth == NULL) return 1;
    fifth->next = sixth;

    Node* seventh = createNode(10);
    if(seventh == NULL) return 1;
    sixth->next = seventh;
    
    printf("Linked list before removing duplicates ");
    printList(head);

    removeDuplicates(head);

    printf("\nLinked list after removing duplicates ");
    printList(head);

    return 0;
}