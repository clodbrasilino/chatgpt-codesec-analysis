#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

Node* createNode(int value, int count) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->count = count;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node* modifiedRunLengthEncoding(int *arr, int n) {
    if (n == 0) return NULL;

    Node *head = NULL;
    Node **current = &head;

    for (int i = 0; i < n; ++i) {
        if (*current == NULL || (*current)->value != arr[i]) {
            *current = createNode(arr[i], 1);
            current = &(*current)->next;
        } else {
            (*current)->count++;
        }
    }

    return head;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d %d\n", head->value, head->count);
        head = head->next;
    }
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node *encodedList = modifiedRunLengthEncoding(arr, n);
    printList(encodedList);

    freeList(encodedList);

    return 0;
}