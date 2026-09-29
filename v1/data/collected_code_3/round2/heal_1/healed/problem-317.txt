#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void modifiedRunLengthEncoding(Node* head) {
    while (head != NULL) {
        int count = 1;
        while (head->next != NULL && head->data == head->next->data) {
            count++;
            head = head->next;
        }
        printf("%d %d ", count, head->data);
        head = head->next;
    }
}

int main() {
    Node* head = newNode(1);
    if (head == NULL) {
    	return -1;
    }
    head->next = newNode(1);
    if (head->next == NULL) {
    	free(head);
    	return -1;
    }
    head->next->next = newNode(2);
    if (head->next->next == NULL) {
        free(head->next);
        free(head);
        return -1;
    }
    head->next->next->next = newNode(2);
    if (head->next->next->next == NULL) {
        free(head->next->next);
        free(head->next);
        free(head);
        return -1;
    }
    head->next->next->next->next = newNode(2);
    if (head->next->next->next->next == NULL) {
        free(head->next->next->next);
        free(head->next->next);
        free(head->next);
        free(head);
        return -1;
    }
    head->next->next->next->next->next = newNode(3);

    modifiedRunLengthEncoding(head);

    return 0;
}