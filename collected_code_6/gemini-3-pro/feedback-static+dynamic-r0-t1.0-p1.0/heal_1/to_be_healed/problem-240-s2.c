#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

struct Node* replaceLastWithList(struct Node* list1, struct Node* list2) {
    if (list1 == NULL) {
        return list2;
    }

    if (list1->next == NULL) {
        free(list1);
        return list2;
    }

    /* Possible weaknesses found:
     *  Assignment 'prev=NULL', assigned value is 0
     */
    struct Node* prev = NULL;
    struct Node* curr = list1;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    free(curr);
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Possible null pointer dereference: prev [nullPointer]
     */
    prev->next = list2;

    return list1;
}

int main(void) {
    struct Node* list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);

    struct Node* list2 = createNode(4);
    list2->next = createNode(5);
    list2->next->next = createNode(6);

    list1 = replaceLastWithList(list1, list2);

    printList(list1);

    freeList(list1);

    return 0;
}