#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

Node *remove_empty_lists(Node *head) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *curr = head;

    while (curr != NULL) {
        Node *next_node = curr->next;
        /* Possible weaknesses found:
         *  Redundant condition: curr->data!=NULL. 'A || (!A && B)' is equivalent to 'A || B' [redundantCondition]
         */
        if (curr->data == NULL || (curr->data != NULL && *((int *)curr->data) == 0)) {
            prev->next = next_node;
            free(curr->data);
            free(curr);
        } else {
            prev = curr;
        }
        curr = next_node;
    }

    return dummy.next;
}

Node *create_node(int is_empty) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    int *data = (int *)malloc(sizeof(int));
    if (data == NULL) {
        free(node);
        exit(EXIT_FAILURE);
    }
    *data = is_empty;
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next_node = curr->next;
        free(curr->data);
        free(curr);
        curr = next_node;
    }
}

int main(void) {
    Node *head = create_node(0);
    head->next = create_node(1);
    head->next->next = create_node(0);
    head->next->next->next = create_node(1);

    Node *curr = head;
    while (curr != NULL) {
        printf("%d ", *((int *)curr->data));
        curr = curr->next;
    }
    printf("\n");

    head = remove_empty_lists(head);

    curr = head;
    while (curr != NULL) {
        printf("%d ", *((int *)curr->data));
        curr = curr->next;
    }
    printf("\n");

    free_list(head);

    return 0;
}