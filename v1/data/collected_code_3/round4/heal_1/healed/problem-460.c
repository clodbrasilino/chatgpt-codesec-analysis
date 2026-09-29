#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (!node) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

void printFirstNode(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
    }
}

int main() {
    struct Node* head1 = newNode(1);
    if (head1 != NULL) {
        head1->next = newNode(2);
        if (head1->next != NULL) {
            head1->next->next = newNode(3);
        }
    }

    struct Node* head2 = newNode(4);
    if (head2 != NULL) {
        head2->next = newNode(5);
        if (head2->next != NULL) {
            head2->next->next = newNode(6);
        }
    }

    struct Node* head3 = newNode(7);
    if (head3 != NULL) {
        head3->next = newNode(8);
        if (head3->next != NULL) {
            head3->next->next = newNode(9);
        }
    }

    printFirstNode(head1);
    printFirstNode(head2);
    printFirstNode(head3);

    return 0;
}