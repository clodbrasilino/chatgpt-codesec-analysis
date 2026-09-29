#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

static bool append_node(Node **head, int data)
{
    Node *new_node;
    Node *current;

    if (head == NULL) {
        return false;
    }

    new_node = create_node(data);
    if (new_node == NULL) {
        return false;
    }

    if (*head == NULL) {
        *head = new_node;
        return true;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return true;
}

static bool select_nth(const Node *head, size_t n, int *result)
{
    const Node *current = head;
    size_t index = 0;

    if (result == NULL) {
        return false;
    }

    while (current != NULL) {
        if (index == n) {
            *result = current->data;
            return true;
        }
        current = current->next;
        index++;
    }
    return false;
}

static void free_list(Node *head)
{
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    Node *head = NULL;
    int values[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;
    size_t n = 2;
    int result = 0;

    for (i = 0; i < count; i++) {
        if (!append_node(&head, values[i])) {
            fprintf(stderr, "Error: failed to append value %d\n", values[i]);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (select_nth(head, n, &result)) {
        printf("Item at index %zu: %d\n", n, result);
    } else {
        fprintf(stderr, "Error: index %zu is out of bounds\n", n);
    }

    if (select_nth(head, 10, &result)) {
        printf("Item at index 10: %d\n", result);
    } else {
        fprintf(stderr, "Error: index 10 is out of bounds\n");
    }

    if (select_nth(NULL, 0, &result)) {
        printf("Item at index 0: %d\n", result);
    } else {
        fprintf(stderr, "Error: list is empty or index invalid\n");
    }

    free_list(head);
    return EXIT_SUCCESS;
}