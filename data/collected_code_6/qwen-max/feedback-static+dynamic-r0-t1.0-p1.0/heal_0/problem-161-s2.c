#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct Node** headRef, int newData) {
    struct Node* newNode = createNode(newData);
    newNode->next = *headRef;
    *headRef = newNode;
}

void removeElementsFirstList(struct Node** headRefA, struct Node* headRefB) {
    struct Node* currentA = *headRefA;
    struct Node* prevA = NULL;
    while (currentA != NULL) {
        struct Node* tempB = headRefB;
        while (tempB != NULL) {
            if (tempB->data == currentA->data) {
                if (prevA == NULL) {
                    *headRefA = currentA->next;
                } else {
                    prevA->next = currentA->next;
                }
                free(currentA);
                currentA = (prevA == NULL) ? *headRefA : prevA->next;
                break;
            }
            tempB = tempB->next;
        }
        if (tempB == NULL) {
            prevA = currentA;
            currentA = currentA->next;
        }
    }
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* headA = NULL;
    struct Node* headB = NULL;

    push(&headA, 5);
    push(&headA, 4);
    push(&headA, 3);
    push(&headA, 2);
    push(&headA, 1);

    push(&headB, 6);
    push(&headB, 5);
    push(&headB, 4);

    printf("List A: ");
    printList(headA);

    printf("List B: ");
    printList(headB);

    removeElementsFirstList(&headA, headB);

    printf("After removing elements from List A present in List B:\n");
    printf("List A: ");
    printList(headA);

    return 0;
}