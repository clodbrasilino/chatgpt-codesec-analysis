#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int split_list(Node *head, size_t n, Node **first_part, Node **second_part) {
    if (!first_part || !second_part) {
        return -1;
    }

    if (n == 0 || !head) {
        *first_part = NULL;
        *second_part = head;
        return 0;
    }

    Node *current = head;
    for (size_t i = 1; i < n; ++i) {
        if (current->next) {
            current = current->next;
        } else {
            break;
        }
    }

    *first_part = head;
    *second_part = current->next;
    current->next = NULL;

    return 0;
}

Node *create_node(int data) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    Node *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(const Node *head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_node(1);
    if (!head) {
        return EXIT_FAILURE;
    }

    Node *current = head;
    for (int i = 2; i <= 5; ++i) {
        current->next = create_node(i);
        if (!current->next) {
            free_list(head);
            return EXIT_FAILURE;
        }
        current = current->next;
    }

    Node *first = NULL;
    Node *second = NULL;

    if (split_list(head, 3, &first, &second) != 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(first);
    print_list(second);

    free_list(first);
    free_list(second);

    return EXIT_SUCCESS;
}