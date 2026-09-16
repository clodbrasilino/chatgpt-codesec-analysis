#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *values;
    size_t length;
    struct Tuple *next;
} Tuple;

static Tuple *create_tuple(size_t length)
{
    Tuple *tuple = malloc(sizeof(*tuple));

    if (tuple == NULL) {
        return NULL;
    }

    tuple->values = NULL;
    tuple->length = length;
    tuple->next = NULL;

    if (length != 0U) {
        if (length > SIZE_MAX / sizeof(*tuple->values)) {
            free(tuple);
            return NULL;
        }

        tuple->values = malloc(length * sizeof(*tuple->values));
        if (tuple->values == NULL) {
            free(tuple);
            return NULL;
        }
    }

    return tuple;
}

static void destroy_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        free(tuple);
    }
}

static void destroy_all_tuples(Tuple *head)
{
    while (head != NULL) {
        Tuple *next = head->next;
        destroy_tuple(head);
        head = next;
    }
}

void remove_tuples_with_length(Tuple **head, size_t k)
{
    Tuple **current;

    if (head == NULL) {
        return;
    }

    current = head;

    while (*current != NULL) {
        Tuple *tuple = *current;

        if (tuple->length == k) {
            *current = tuple->next;
            destroy_tuple(tuple);
        } else {
            current = &tuple->next;
        }
    }
}

static int print_tuples(const Tuple *head)
{
    size_t count = 0U;
    const Tuple *current;

    for (current = head; current != NULL; current = current->next) {
        ++count;
    }

    if (printf("%zu\n", count) < 0) {
        return 0;
    }

    for (current = head; current != NULL; current = current->next) {
        size_t i;

        if (printf("%zu", current->length) < 0) {
            return 0;
        }

        for (i = 0U; i < current->length; ++i) {
            if (printf(" %d", current->values[i]) < 0) {
                return 0;
            }
        }

        if (putchar('\n') == EOF) {
            return 0;
        }
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
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < tuple_count; ++i) {
        Tuple *tuple;
        size_t length;
        size_t j;

        if (scanf("%zu", &length) != 1) {
            fputs("Invalid tuple length\n", stderr);
            destroy_all_tuples(head);
            return EXIT_FAILURE;
        }

        tuple = create_tuple(length);
        if (tuple == NULL) {
            fputs("Unable to allocate memory\n", stderr);
            destroy_all_tuples(head);
            return EXIT_FAILURE;
        }

        for (j = 0U; j < length; ++j) {
            if (scanf("%d", &tuple->values[j]) != 1) {
                fputs("Invalid tuple value\n", stderr);
                destroy_tuple(tuple);
                destroy_all_tuples(head);
                return EXIT_FAILURE;
            }
        }

        *tail = tuple;
        tail = &tuple->next;
    }

    if (scanf("%zu", &k) != 1) {
        fputs("Invalid removal length\n", stderr);
        destroy_all_tuples(head);
        return EXIT_FAILURE;
    }

    remove_tuples_with_length(&head, k);

    if (!print_tuples(head) || fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        destroy_all_tuples(head);
        return EXIT_FAILURE;
    }

    destroy_all_tuples(head);
    return EXIT_SUCCESS;
}