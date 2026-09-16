#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;

    while (curr != NULL) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

void reverse_each_list(Node **lists, size_t count) {
    if (lists == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        lists[i] = reverse_list(lists[i]);
    }
}

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->data = data;
    node->next = NULL;

    return node;
}

Node *build_list(const int *values, size_t count) {
    if (values == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    for (size_t i = 0; i < count; ++i) {
        Node *node = create_node(values[i]);

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    const int values1[] = {1, 2, 3, 4};
    const int values2[] = {5, 6, 7};
    const int values3[] = {8, 9};

    Node *lists[3];

    lists[0] = build_list(values1, 4);
    lists[1] = build_list(values2, 3);
    lists[2] = build_list(values3, 2);

    printf("Original lists:\n");
    for (size_t i = 0; i < 3; ++i) {
        print_list(lists[i]);
    }

    reverse_each_list(lists, 3);

    printf("Reversed lists:\n");
    for (size_t i = 0; i < 3; ++i) {
        print_list(lists[i]);
    }

    for (size_t i = 0; i < 3; ++i) {
        free_list(lists[i]);
    }

    return 0;
}