#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

static struct node *create_node(int value)
{
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->value = value;
    n->next = NULL;
    return n;
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

static struct node *build_list(const int *values, size_t count)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        struct node *n = create_node(values[i]);
        if (n == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = n;
        } else {
            tail->next = n;
        }
        tail = n;
    }
    return head;
}

static size_t list_length(const struct node *head)
{
    size_t len = 0;

    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

static struct node *interleave(struct node *a, struct node *b)
{
    struct node *head = NULL;
    struct node *tail = NULL;

    if (list_length(a) != list_length(b)) {
        return NULL;
    }

    while (a != NULL && b != NULL) {
        struct node *next_a = a->next;
        struct node *next_b = b->next;

        if (head == NULL) {
            head = a;
        } else {
            tail->next = a;
        }
        a->next = b;
        tail = b;
        tail->next = NULL;

        a = next_a;
        b = next_b;
    }
    return head;
}

static void print_list(const struct node *head)
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
    int values_a[] = {1, 3, 5, 7};
    int values_b[] = {2, 4, 6, 8};
    struct node *list_a;
    struct node *list_b;
    struct node *merged;

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

    merged = interleave(list_a, list_b);
    if (merged == NULL) {
        fprintf(stderr, "Lists have different lengths\n");
        free_list(list_a);
        free_list(list_b);
        return EXIT_FAILURE;
    }

    print_list(merged);
    free_list(merged);

    return EXIT_SUCCESS;
}