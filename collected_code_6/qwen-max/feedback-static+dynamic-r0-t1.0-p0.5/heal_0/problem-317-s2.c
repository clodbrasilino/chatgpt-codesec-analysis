#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int freq;
    struct Node *next;
} Node;

Node* createNode(int val, int freq) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->val = val;
    newNode->freq = freq;
    newNode->next = NULL;
    return newNode;
}

void addNode(Node **head, int val, int freq) {
    Node *newNode = createNode(val, freq);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Node* modifiedRunLengthEncoding(int *arr, int n) {
    if (n == 0) return NULL;
    Node *head = NULL;
    int currentVal = arr[0];
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == currentVal) {
            count++;
        } else {
            addNode(&head, currentVal, count);
            currentVal = arr[i];
            count = 1;
        }
    }
    addNode(&head, currentVal, count);
    return head;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d %d -> ", head->val, head->freq);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *encodedList = modifiedRunLengthEncoding(arr, n);
    printList(encodedList);
    return 0;
}