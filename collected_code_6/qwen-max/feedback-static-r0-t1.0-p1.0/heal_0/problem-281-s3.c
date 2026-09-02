#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int areElementsUnique(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *runner = current->next;
        while (runner != NULL) {
            if (current->data == runner->data) {
                return 0;
            }
            runner = runner->next;
        }
        current = current->next;
    }
    return 1;
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(1);

    if (areElementsUnique(head)) {
        printf("All elements are unique.\n");
    } else {
        printf("There are duplicate elements.\n");
    }

    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}