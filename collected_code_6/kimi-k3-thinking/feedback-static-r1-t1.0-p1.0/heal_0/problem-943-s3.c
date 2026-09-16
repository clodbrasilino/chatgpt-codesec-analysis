#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
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

static struct Node *build_list(const int *values, size_t count)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; ++i) {
        struct Node *node = create_node(values[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    return head;
}

static struct Node *merge_sorted(struct Node *a, struct Node *b)
{
    struct Node dummy;
    struct Node *tail;

    dummy.data = 0;
    dummy.next = NULL;
    tail = &dummy;

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a != NULL) ? a : b;

    return dummy.next;
}

static void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            putchar(' ');
        }
        current = current->next;
    }
    putchar('\n');
}

int main(void)
{
    const int values_a[] = {1, 3, 5, 7, 9};
    const int values_b[] = {2, 4, 6, 8, 10};
    struct Node *list_a;
    struct Node *list_b;
    struct Node *merged;

    list_a = build_list(values_a, sizeof values_a / sizeof values_a[0]);
    if (list_a == NULL) {
        fprintf(stderr, "error: unable to build list A\n");
        return EXIT_FAILURE;
    }

    list_b = build_list(values_b, sizeof values_b / sizeof values_b[0]);
    if (list_b == NULL) {
        fprintf(stderr, "error: unable to build list B\n");
        free_list(list_a);
        return EXIT_FAILURE;
    }

    printf("List A: ");
    print_list(list_a);
    printf("List B: ");
    print_list(list_b);

    merged = merge_sorted(list_a, list_b);
    list_a = NULL;
    list_b = NULL;

    printf("Merged: ");
    print_list(merged);

    free_list(merged);
    merged = NULL;

    return EXIT_SUCCESS;
}