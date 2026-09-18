#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

Node* replaceLastWithList(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    }

    if (list1->next == NULL) {
        free(list1);
        return list2;
    }

    Node* current = list1;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = list2;

    return list1;
}

int main(void) {
    Node* list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);

    Node* list2 = createNode(4);
    list2->next = createNode(5);

    list1 = replaceLastWithList(list1, list2);

    printList(list1);

    freeList(list1);

    return 0;
}