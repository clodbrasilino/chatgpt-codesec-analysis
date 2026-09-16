#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *items;
    size_t length;
    struct Tuple *next;
} Tuple;

static void free_tuples(Tuple *head)
{
    while (head != NULL) {
        Tuple *next = head->next;
        free(head->items);
        free(head);
        head = next;
    }
}

size_t remove_tuples_with_length(Tuple **head, size_t k)
{
    Tuple **current;
    size_t removed = 0;

    if (head == NULL) {
        return 0;
    }

    current = head;

    while (*current != NULL) {
        Tuple *tuple = *current;

        if (tuple->length == k) {
            *current = tuple->next;
            free(tuple->items);
            free(tuple);
            ++removed;
        } else {
            current = &tuple->next;
        }
    }

    return removed;
}

static int print_tuples(const Tuple *head)
{
    while (head != NULL) {
        size_t i;

        if (putchar('(') == EOF) {
            return 0;
        }

        for (i = 0; i < head->length; ++i) {
            if (i > 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (printf("%d", head->items[i]) < 0) {
                return 0;
            }
        }

        if (puts(")") == EOF) {
            return 0;
        }

        head = head->next;
    }

    return 1;
}

int main(void)
{
    Tuple *head = NULL;
    Tuple **tail = &head;
    size_t tuple_count;
    size_t k;
    size_t i;

    if (scanf("%zu", &tuple_count) != 1) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        Tuple *tuple;
        size_t j;

        tuple = calloc(1, sizeof(*tuple));
        if (tuple == NULL) {
            free_tuples(head);
            return EXIT_FAILURE;
        }

        if (scanf("%zu", &tuple->length) != 1) {
            free(tuple);
            free_tuples(head);
            return EXIT_FAILURE;
        }

        if (tuple->length > SIZE_MAX / sizeof(*tuple->items)) {
            free(tuple);
            free_tuples(head);
            return EXIT_FAILURE;
        }

        if (tuple->length > 0) {
            tuple->items = malloc(tuple->length * sizeof(*tuple->items));
            if (tuple->items == NULL) {
                free(tuple);
                free_tuples(head);
                return EXIT_FAILURE;
            }
        }

        for (j = 0; j < tuple->length; ++j) {
            if (scanf("%d", &tuple->items[j]) != 1) {
                free(tuple->items);
                free(tuple);
                free_tuples(head);
                return EXIT_FAILURE;
            }
        }

        *tail = tuple;
        tail = &tuple->next;
    }

    if (scanf("%zu", &k) != 1) {
        free_tuples(head);
        return EXIT_FAILURE;
    }

    remove_tuples_with_length(&head, k);

    if (!print_tuples(head) || fflush(stdout) == EOF) {
        free_tuples(head);
        return EXIT_FAILURE;
    }

    free_tuples(head);
    return EXIT_SUCCESS;
}