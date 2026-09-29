#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
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

int append_node(struct Node **head, struct Node **tail, int value)
{
    struct Node *node = create_node(value);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;
    return 0;
}

struct Node *add_lists(const struct Node *a, const struct Node *b)
{
    struct Node *result = NULL;
    struct Node *tail = NULL;

    while (a != NULL && b != NULL) {
        if (append_node(&result, &tail, a->value + b->value) != 0) {
            free_list(result);
            return NULL;
        }
        a = a->next;
        b = b->next;
    }

    while (a != NULL) {
        if (append_node(&result, &tail, a->value) != 0) {
            free_list(result);
            return NULL;
        }
        a = a->next;
    }

    while (b != NULL) {
        if (append_node(&result, &tail, b->value) != 0) {
            free_list(result);
            return NULL;
        }
        b = b->next;
    }

    return result;
}

struct Node *build_list(const int *values, size_t count)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        if (append_node(&head, &tail, values[i]) != 0) {
            free_list(head);
            return NULL;
        }
    }
    return head;
}

void print_list(const struct Node *head)
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
    int values_a[] = {1, 2, 3, 4};
    int values_b[] = {10, 20, 30};
    struct Node *list_a = NULL;
    struct Node *list_b = NULL;
    struct Node *sum = NULL;

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

    sum = add_lists(list_a, list_b);
    if (sum == NULL) {
        fprintf(stderr, "Failed to add lists\n");
        free_list(list_a);
        free_list(list_b);
        return EXIT_FAILURE;
    }

    print_list(list_a);
    print_list(list_b);
    print_list(sum);

    free_list(list_a);
    free_list(list_b);
    free_list(sum);

    return EXIT_SUCCESS;
}