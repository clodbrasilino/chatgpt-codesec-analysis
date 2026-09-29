#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int findMaxSublistLength(Node **lists, int n) {
    int max_length = 0;
    for (int i = 0; i < n; ++i) {
        Node *current = lists[i];
        int length = 0;
        while (current != NULL) {
            current = current->next;
            ++length;
        }
        if (length > max_length) {
            max_length = length;
        }
    }
    return max_length;
}

int main() {
    Node *list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);

    Node *list2 = createNode(4);
    list2->next = createNode(5);

    Node *list3 = createNode(6);
    list3->next = createNode(7);
    list3->next->next = createNode(8);
    list3->next->next->next = createNode(9);

    Node *lists[3] = {list1, list2, list3};

    int n = sizeof(lists) / sizeof(lists[0]);
    int maxLength = findMaxSublistLength(lists, n);

    printf("Maximum sublist length is: %d\n", maxLength);

    // Free allocated memory
    for (int i = 0; i < n; ++i) {
        Node *current = lists[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}