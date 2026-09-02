#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* shiftLastToFirst(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node *last = head, *second_last = NULL;
    while (last->next != NULL) {
        second_last = last;
        last = last->next;
    }
    if (second_last != NULL) {
        second_last->next = NULL;
    }
    last->next = head;
    head = last;
    return head;
}

void printList(Node *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = (Node*)malloc(sizeof(Node));
    head->next->data = 2;
    head->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->data = 3;
    head->next->next->next = NULL;

    printf("Original List: ");
    printList(head);

    head = shiftLastToFirst(head);

    printf("Modified List: ");
    printList(head);

    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}