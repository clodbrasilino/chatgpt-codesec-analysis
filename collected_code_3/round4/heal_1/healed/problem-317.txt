#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* modifiedRunLengthEncoding(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;

    Node* prev = head;
    Node* curr = head->next;

    while (curr != NULL) {
        if (prev->data == curr->data) {
            int count = 2;
            while (curr->next != NULL && curr->next->data == prev->data) {
                count++;
                curr = curr->next;
            }
            prev->next = createNode(count);
            prev = curr;
            curr = curr->next;
        } else {
            prev->next = createNode(1);
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    if (head == NULL) exit(1);
    
    Node *node = createNode(1);
    if (node == NULL) exit(1);
    head->next = node;

    node = createNode(2);
    if (node == NULL) exit(1);
    head->next->next = node;

    node = createNode(2);
    if (node == NULL) exit(1);
    head->next->next->next = node;

    node = createNode(2);
    if (node == NULL) exit(1);
    head->next->next->next->next = node;

    node = createNode(3);
    if (node == NULL) exit(1);
    head->next->next->next->next->next = node;

    printf("Original List: ");
    printList(head);

    Node* result = modifiedRunLengthEncoding(head);

    printf("Modified Run-Length Encoded List: ");
    printList(result);

    return 0;
}