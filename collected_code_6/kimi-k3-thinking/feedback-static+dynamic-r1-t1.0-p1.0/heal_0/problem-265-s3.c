#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node **parts;
    size_t count;
} SplitResult;

static Node *create_node(int data)
{
    Node *node = (Node *)malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static int append_node(Node **head, int data)
{
    Node *node;
    Node *tail;

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

    tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return 0;
}

static void free_list(Node *head)
{
    Node *next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}

static void destroy_split(SplitResult *result)
{
    size_t i;

    if (result == NULL) {
        return;
    }

    for (i = 0; i < result->count; i++) {
        free_list(result->parts[i]);
        result->parts[i] = NULL;
    }

    free(result->parts);
    result->parts = NULL;
    result->count = 0;
}

static void print_list(const Node *head)
{
    putchar('[');
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("]\n");
}

SplitResult split_list(Node *head, size_t n)
{
    SplitResult result;
    Node *current;
    Node *next;
    size_t len;
    size_t num_parts;
    size_t part_index;
    size_t in_part;

    result.parts = NULL;
    result.count = 0;

    if (head == NULL || n == 0) {
        return result;
    }

    len = 0;
    for (current = head; current != NULL; current = current->next) {
        len++;
    }

    num_parts = len / n + ((len % n) != 0);

    result.parts = (Node **)calloc(num_parts, sizeof(*result.parts));
    if (result.parts == NULL) {
        return result;
    }

    result.count = num_parts;
    result.parts[0] = head;
    part_index = 0;
    in_part = 0;
    current = head;

    while (current != NULL) {
        in_part++;
        if (in_part == n && current->next != NULL) {
            next = current->next;
            current->next = NULL;
            part_index++;
            result.parts[part_index] = next;
            current = next;
            in_part = 0;
        } else {
            current = current->next;
        }
    }

    return result;
}

int main(void)
{
    Node *head = NULL;
    SplitResult result;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t n = 3;
    size_t i;

    for (i = 0; i < num_values; i++) {
        if (append_node(&head, values[i]) != 0) {
            fprintf(stderr, "Failed to build list\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    result = split_list(head, n);
    if (result.parts == NULL) {
        fprintf(stderr, "Failed to split list\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Split every %zu elements:\n", n);
    for (i = 0; i < result.count; i++) {
        printf("Part %zu: ", i + 1);
        print_list(result.parts[i]);
    }

    destroy_split(&result);

    return EXIT_SUCCESS;
}