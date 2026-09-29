#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node* run_length_encode(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* result = NULL;
    Node** nextPtr = &result;
    Node* current = head;

    while(current != NULL) {
        int count = 1;
        while (current->next != NULL && current->next->val == current->val) {
            count++;
            current = current->next;
        }

        *nextPtr = malloc(sizeof(Node));
        if (*nextPtr == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        (*nextPtr)->val = count;
        (*nextPtr)->next = NULL;
        nextPtr = &(*nextPtr)->next;
        current = current->next;
    }
    return result;
}

int main() {
    Node n3 = {3, NULL};
    Node n2 = {2, &n3};
    Node n1 = {2, &n2};
    Node n0 = {1, &n1};

    Node* encoded_list = run_length_encode(&n0);
    Node* current = encoded_list;
    while (current != NULL) {
        printf("%d ", current->val);
        Node* prev = current;
        current = current->next;
        free(prev);
    }
    return 0;
}