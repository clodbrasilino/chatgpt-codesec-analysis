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
        return NULL;
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
    head->next = createNode(1);
    head->next->next = createNode(2);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(2);
    head->next->next->next->next->next = createNode(3);

    printf("Original List: ");
    printList(head);

    Node* result = modifiedRunLengthEncoding(head);

    printf("Modified Run-Length Encoded List: ");
    printList(result);

    return 0;
}