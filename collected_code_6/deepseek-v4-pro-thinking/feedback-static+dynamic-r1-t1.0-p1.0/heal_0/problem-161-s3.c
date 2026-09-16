#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static int contains(const Node *head, int value) {
    const Node *current = head;

    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void remove_elements(Node **head, const Node *other) {
    Node **current = head;

    if (head == NULL || other == NULL) {
        return;
    }

    while (*current != NULL) {
        if (contains(other, (*current)->data)) {
            Node *removed = *current;
            *current = removed->next;
            free(removed);
        } else {
            current = &(*current)->next;
        }
    }
}

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void append_node(Node **head, int data) {
    Node *node = create_node(data);

    if (*head == NULL) {
        *head = node;
        return;
    }

    Node *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = node;
}

void print_list(const Node *head) {
    const Node *current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    int values1[] = {1, 2, 3, 4, 5};
    int values2[] = {2, 4, 6};
    size_t i;

    for (i = 0; i < sizeof(values1) / sizeof(values1[0]); i++) {
        append_node(&list1, values1[i]);
    }

    for (i = 0; i < sizeof(values2) / sizeof(values2[0]); i++) {
        append_node(&list2, values2[i]);
    }

    print_list(list1);
    print_list(list2);

    remove_elements(&list1, list2);

    print_list(list1);

    free_list(list1);
    free_list(list2);

    return 0;
}