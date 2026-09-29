#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeKthNode(struct Node** head, int k) {
    struct Node* temp = *head, *prev = NULL;
    if(k == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    for(int i = 0; temp != NULL && i < k; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void push(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

int main() {
    struct Node* head = NULL;

    push(&head, 7);
    push(&head, 6);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printf("Given linked list: ");
    printList(head);

    int k = 4;
    removeKthNode(&head, k - 1);

    printf("New linked list after removing %d'th element: ", k);
    printList(head);

    return 0;
}