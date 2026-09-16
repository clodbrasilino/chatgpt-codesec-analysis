#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

bool areTuplesEqual(Tuple t1, Tuple t2) {
    return (t1.first == t2.first && t1.second == t2.second);
}

Node* createNode(Tuple data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

bool areListsIdentical(Node* head1, Node* head2) {
    Node* current1 = head1;
    Node* current2 = head2;

    while (current1 != NULL && current2 != NULL) {
        if (!areTuplesEqual(current1->data, current2->data)) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return (current1 == NULL && current2 == NULL);
}

int main() {
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};

    Node* head1 = createNode(t1);
    head1->next = createNode(t2);

    Tuple t3 = {1, 2};
    Tuple t4 = {3, 4};

    Node* head2 = createNode(t3);
    head2->next = createNode(t4);

    if (areListsIdentical(head1, head2)) {
        printf("The lists are identical.\n");
    } else {
        printf("The lists are not identical.\n");
    }

    return 0;
}