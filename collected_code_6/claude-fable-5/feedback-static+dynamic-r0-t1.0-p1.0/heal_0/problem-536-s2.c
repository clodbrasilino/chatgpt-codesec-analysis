#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int append(struct Node **head, int data)
{
    struct Node *node;
    struct Node *current;

    if (head == NULL) {
        return -1;
    }

    node = create_node(data);
    if (node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

int get_nth(const struct Node *head, size_t n, int *out)
{
    const struct Node *current = head;
    size_t index = 0;

    if (out == NULL) {
        return -1;
    }

    while (current != NULL) {
        if (index == n) {
            *out = current->data;
            return 0;
        }
        index++;
        current = current->next;
    }
    return -1;
}

void free_list(struct Node *head)
{
    struct Node *current = head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    struct Node *head = NULL;
    int value = 0;
    size_t i;
    size_t n = 3;

    for (i = 0; i < 5; i++) {
        if (append(&head, (int)(i * 10)) != 0) {
            fprintf(stderr, "Failed to append node\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (get_nth(head, n, &value) != 0) {
        fprintf(stderr, "Index %zu out of range\n", n);
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Element at index %zu is %d\n", n, value);

    free_list(head);
    return EXIT_SUCCESS;
}