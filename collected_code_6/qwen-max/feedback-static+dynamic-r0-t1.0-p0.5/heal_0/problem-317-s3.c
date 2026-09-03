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
        return NULL;
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
    if (n == 0) {
        return NULL;
    }

    Node *head = createNode(arr[0], 1);
    if (head == NULL) {
        return NULL;
    }

    Node *current = head;
    for (int i = 1; i < n; i++) {
        if (arr[i] == current->value) {
            current->count++;
        } else {
            current->next = createNode(arr[i], 1);
            if (current->next == NULL) {
                freeList(head);
                return NULL;
            }
            current = current->next;
        }
    }
    return head;
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("(%d, %d) ", current->value, current->count);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node *encodedList = modifiedRunLengthEncoding(arr, n);
    if (encodedList == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printList(encodedList);

    freeList(encodedList);
    return 0;
}