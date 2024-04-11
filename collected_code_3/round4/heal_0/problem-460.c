#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
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
    head1->next = newNode(2);
    head1->next->next = newNode(3);

    struct Node* head2 = newNode(4);
    head2->next = newNode(5);
    head2->next->next = newNode(6);

    struct Node* head3 = newNode(7);
    head3->next = newNode(8);
    head3->next->next = newNode(9);

    printFirstNode(head1);
    printFirstNode(head2);
    printFirstNode(head3);

    return 0;
}