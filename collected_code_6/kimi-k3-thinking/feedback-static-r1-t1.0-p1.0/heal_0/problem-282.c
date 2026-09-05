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

static void free_list(Node *head)
{
    Node *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

static int append_node(Node **head, int data)
{
    Node *node;
    Node *current;

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

static int subtract_lists(const Node *a, const Node *b, Node **result)
{
    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    while (a != NULL && b != NULL) {
        if (append_node(result, a->data - b->data) != 0) {
            free_list(*result);
            *result = NULL;
            return -1;
        }
        a = a->next;
        b = b->next;
    }

    return 0;
}

static void print_list(const Node *head)
{
    if (head == NULL) {
        printf("(empty)");
    }

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
    Node *list_a = NULL;
    Node *list_b = NULL;
    Node *result = NULL;
    const int values_a[] = {10, 20, 30, 40, 50};
    const int values_b[] = {1, 2, 3, 4, 5};
    const size_t count_a = sizeof(values_a) / sizeof(values_a[0]);
    const size_t count_b = sizeof(values_b) / sizeof(values_b[0]);
    size_t i;
    int exit_code = EXIT_FAILURE;

    for (i = 0; i < count_a; i++) {
        if (append_node(&list_a, values_a[i]) != 0) {
            fprintf(stderr, "Error: failed to build list A\n");
            goto cleanup;
        }
    }

    for (i = 0; i < count_b; i++) {
        if (append_node(&list_b, values_b[i]) != 0) {
            fprintf(stderr, "Error: failed to build list B\n");
            goto cleanup;
        }
    }

    if (subtract_lists(list_a, list_b, &result) != 0) {
        fprintf(stderr, "Error: failed to subtract lists\n");
        goto cleanup;
    }

    printf("List A: ");
    print_list(list_a);
    printf("List B: ");
    print_list(list_b);
    printf("A - B:  ");
    print_list(result);

    exit_code = EXIT_SUCCESS;

cleanup:
    free_list(list_a);
    free_list(list_b);
    free_list(result);
    return exit_code;
}