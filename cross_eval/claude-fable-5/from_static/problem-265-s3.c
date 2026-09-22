#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

struct Node *build_list(const int *values, size_t count)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        struct Node *node = create_node(values[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    return head;
}

size_t list_length(const struct Node *head)
{
    size_t len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

struct Node **split_every_nth(struct Node *head, size_t n, size_t *out_count)
{
    struct Node **parts;
    struct Node *current;
    size_t total;
    size_t num_parts;
    size_t part_index;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (head == NULL || n == 0) {
        return NULL;
    }

    total = list_length(head);
    num_parts = (total + n - 1) / n;

    parts = malloc(num_parts * sizeof(struct Node *));
    if (parts == NULL) {
        return NULL;
    }

    current = head;
    for (part_index = 0; part_index < num_parts; part_index++) {
        parts[part_index] = current;
        for (i = 0; i < n - 1 && current->next != NULL; i++) {
            current = current->next;
        }
        if (current != NULL) {
            struct Node *next_part = current->next;
            current->next = NULL;
            current = next_part;
        }
    }

    *out_count = num_parts;
    return parts;
}

void print_list(const struct Node *head)
{
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t value_count = sizeof(values) / sizeof(values[0]);
    struct Node *head;
    struct Node **parts;
    size_t part_count;
    size_t i;
    size_t n = 3;

    head = build_list(values, value_count);
    if (head == NULL) {
        fprintf(stderr, "Failed to build list\n");
        return EXIT_FAILURE;
    }

    printf("Original list:\n");
    print_list(head);

    parts = split_every_nth(head, n, &part_count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split list\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Split into groups of %zu:\n", n);
    for (i = 0; i < part_count; i++) {
        printf("Part %zu: ", i + 1);
        print_list(parts[i]);
    }

    for (i = 0; i < part_count; i++) {
        free_list(parts[i]);
    }
    free(parts);

    return EXIT_SUCCESS;
}