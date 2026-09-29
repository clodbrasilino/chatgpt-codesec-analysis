#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL)
        return;

    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

struct Node* minLenSublist(struct Node* head) {
    struct Node* minSublist = NULL;
    int minLen = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        struct Node* sublist = temp;
        int len = 0;
        while (sublist != NULL) {
            len++;
            sublist = sublist->next;
        }
        if (minLen == 0 || len < minLen) {
            minLen = len;
            minSublist = temp;
        }
        temp = temp->next;
    }
    return minSublist;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    push(&head, 20);
    push(&head, 4);
    push(&head, 15);
    push(&head, 10);
    struct Node* minSublist = minLenSublist(head);
    printList(minSublist);
    return 0;
}