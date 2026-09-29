#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

static struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->next = NULL;

    return node;
}

static void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

static struct Node *append_node(struct Node *head, struct Node **tail, int value)
{
    struct Node *node = create_node(value);

    if (node == NULL) {
        free_list(head);
        return NULL;
    }

    if (head == NULL) {
        *tail = node;
        return node;
    }

    (*tail)->next = node;
    *tail = node;

    return head;
}

static struct Node *build_list(const int *values, size_t count)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        head = append_node(head, &tail, values[i]);
        if (head == NULL) {
            return NULL;
        }
    }

    return head;
}

static struct Node *subtract_lists(const struct Node *a, const struct Node *b)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    while (a != NULL && b != NULL) {
        head = append_node(head, &tail, a->value - b->value);
        if (head == NULL) {
            return NULL;
        }
        a = a->next;
        b = b->next;
    }

    return head;
}

static void print_list(const struct Node *head)
{
    while (head != NULL) {
        printf("%d", head->value);
        if (head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int values_a[] = {10, 20, 30, 40};
    int values_b[] = {1, 2, 3, 4};
    struct Node *list_a = NULL;
    struct Node *list_b = NULL;
    struct Node *result = NULL;

    list_a = build_list(values_a, sizeof(values_a) / sizeof(values_a[0]));
    if (list_a == NULL) {
        fprintf(stderr, "Failed to build first list\n");
        return EXIT_FAILURE;
    }

    list_b = build_list(values_b, sizeof(values_b) / sizeof(values_b[0]));
    if (list_b == NULL) {
        fprintf(stderr, "Failed to build second list\n");
        free_list(list_a);
        return EXIT_FAILURE;
    }

    result = subtract_lists(list_a, list_b);
    if (result == NULL) {
        fprintf(stderr, "Failed to subtract lists\n");
        free_list(list_a);
        free_list(list_b);
        return EXIT_FAILURE;
    }

    print_list(list_a);
    print_list(list_b);
    print_list(result);

    free_list(list_a);
    free_list(list_b);
    free_list(result);

    return EXIT_SUCCESS;
}