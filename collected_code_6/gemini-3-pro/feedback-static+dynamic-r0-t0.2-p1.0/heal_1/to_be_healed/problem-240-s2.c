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

Node* replaceLastWithList(Node* head1, Node* head2) {
    if (head1 == NULL) {
        return head2;
    }

    if (head1->next == NULL) {
        free(head1);
        return head2;
    }

    Node* current = head1;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = head2;

    return head1;
}

int main() {
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