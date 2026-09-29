#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static int list_contains(const Node *head, int value)
{
    const Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

static int append_node(Node **head, Node **tail, int data)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return 0;
    }

    node = create_node(data);
    if (node == NULL) {
        return 0;
    }

    if (*head == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;
    return 1;
}

void free_list(Node *head)
{
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int list_difference(const Node *first, const Node *second, Node **result)
{
    Node *result_head = NULL;
    Node *result_tail = NULL;
    const Node *current;

    if (result == NULL) {
        return -1;
    }
    *result = NULL;

    for (current = first; current != NULL; current = current->next) {
        if (!list_contains(second, current->data) &&
            !list_contains(result_head, current->data)) {
            if (!append_node(&result_head, &result_tail, current->data)) {
                free_list(result_head);
                return -1;
            }
        }
    }

    *result = result_head;
    return 0;
}

static void print_list(const Node *head)
{
    const Node *current = head;
    if (current == NULL) {
        printf("(empty)");
    }
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void)
{
    Node *list_a = NULL;
    Node *list_b = NULL;
    Node *tail_a = NULL;
    Node *tail_b = NULL;
    Node *diff = NULL;
    const int values_a[] = {1, 2, 3, 4, 5, 2};
    const int values_b[] = {3, 4, 6};
    size_t i;

    for (i = 0; i < sizeof(values_a) / sizeof(values_a[0]); ++i) {
        if (!append_node(&list_a, &tail_a, values_a[i])) {
            fprintf(stderr, "error: failed to build list A\n");
            free_list(list_a);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < sizeof(values_b) / sizeof(values_b[0]); ++i) {
        if (!append_node(&list_b, &tail_b, values_b[i])) {
            fprintf(stderr, "error: failed to build list B\n");
            free_list(list_a);
            free_list(list_b);
            return EXIT_FAILURE;
        }
    }

    if (list_difference(list_a, list_b, &diff) != 0) {
        fprintf(stderr, "error: failed to compute list difference\n");
        free_list(list_a);
        free_list(list_b);
        return EXIT_FAILURE;
    }

    printf("List A: ");
    print_list(list_a);
    printf("List B: ");
    print_list(list_b);
    printf("Difference (A - B): ");
    print_list(diff);

    free_list(list_a);
    free_list(list_b);
    free_list(diff);

    return EXIT_SUCCESS;
}