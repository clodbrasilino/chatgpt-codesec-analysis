#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *alternate_list(Node *head) {
    if (head == NULL) {
        return NULL;
    }

    Node *new_head = create_node(head->data);
    Node *current = new_head;
    Node *src = head->next;

    int take = 0;
    while (src != NULL) {
        if (take) {
            current->next = create_node(src->data);
            current = current->next;
        }
        take = !take;
        src = src->next;
    }

    return new_head;
}

void free_list(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node *head = create_node(1);
    Node *current = head;
    for (int i = 2; i <= 6; ++i) {
        current->next = create_node(i);
        current = current->next;
    }

    Node *alt_head = alternate_list(head);

    current = alt_head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(head);
    free_list(alt_head);

    return 0;
}