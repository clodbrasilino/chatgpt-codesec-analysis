#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* find_max_length_sublist(Node *head) {
    if (head == NULL) {
        return NULL;
    }

    Node *max_start = head;
    int max_len = 1;

    Node *current_start = head;
    int current_len = 1;
    Node *current = head;

    while (current->next != NULL) {
        if (current->data <= current->next->data) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
                max_start = current_start;
            }
            current_start = current->next;
            current_len = 1;
        }
        current = current->next;
    }

    if (current_len > max_len) {
        max_start = current_start;
    }

    return max_start;
}

void free_list(Node *head) {
    Node *current = head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(1);
    head->next->next->next->next = create_node(2);
    head->next->next->next->next->next = create_node(3);
    head->next->next->next->next->next->next = create_node(4);
    head->next->next->next->next->next->next->next = create_node(5);

    /* Possible weaknesses found:
     *  Variable 'max_sublist' can be declared as pointer to const [constVariablePointer]
     */
    Node *max_sublist = find_max_length_sublist(head);

    if (max_sublist != NULL) {
        printf("Sublist with maximum length starts at node with data: %d\n", max_sublist->data);
    } else {
        printf("List is empty.\n");
    }

    free_list(head);

    return 0;
}