#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

void getFirstElement(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
    }
}

int main() {
    struct Node* head = newNode(1);
    if (head == NULL) {
        return 1;
    }

    struct Node* current = head;

    for (int i = 2; i <= 5; ++i) {
        current->next = newNode(i);
        if (current->next == NULL) {
            return 1;
        }
        current = current->next;  
    }    

    getFirstElement(head);

    return 0;
}