#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* removeNegatives(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = newNode(-5);
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    head->next = newNode(10);
    if (head->next == NULL) {
        return EXIT_FAILURE;
    }
    
    head->next->next = newNode(-15);
    if (head->next->next == NULL) {
        return EXIT_FAILURE;
    }
    
    head->next->next->next = newNode(20);
    if (head->next->next->next == NULL) {
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    printList(head);

    head = removeNegatives(head);

    printf("List after removing negatives: ");
    printList(head);

    return EXIT_SUCCESS;
}