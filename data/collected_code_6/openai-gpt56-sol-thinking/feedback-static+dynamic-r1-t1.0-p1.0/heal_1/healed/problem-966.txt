#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *values;
    size_t length;
    struct Tuple *next;
} Tuple;

typedef struct {
    Tuple *head;
    Tuple *tail;
} TupleList;

static Tuple *tuple_create(const int *values, size_t length)
{
    Tuple *tuple;
    size_t index;

    if (length > 0 && values == NULL) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(*values)) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->values = NULL;
    tuple->length = length;
    tuple->next = NULL;

    if (length > 0) {
        tuple->values = malloc(length * sizeof(*tuple->values));
        if (tuple->values == NULL) {
            free(tuple);
            return NULL;
        }

        for (index = 0; index < length; ++index) {
            tuple->values[index] = values[index];
        }
    }

    return tuple;
}

static int tuple_list_append(TupleList *list, const int *values, size_t length)
{
    Tuple *tuple;

    if (list == NULL) {
        return -1;
    }

    tuple = tuple_create(values, length);
    if (tuple == NULL) {
        return -1;
    }

    if (list->tail == NULL) {
        list->head = tuple;
        list->tail = tuple;
    } else {
        list->tail->next = tuple;
        list->tail = tuple;
    }

    return 0;
}

static size_t remove_empty_tuples(TupleList *list)
{
    Tuple *current;
    Tuple *previous = NULL;
    size_t removed = 0;

    if (list == NULL) {
        return 0;
    }

    current = list->head;

    while (current != NULL) {
        Tuple *next = current->next;

        if (current->length == 0) {
            if (previous == NULL) {
                list->head = next;
            } else {
                previous->next = next;
            }

            if (list->tail == current) {
                list->tail = previous;
            }

            free(current->values);
            free(current);
            ++removed;
        } else {
            previous = current;
        }

        current = next;
    }

    if (list->head == NULL) {
        list->tail = NULL;
    }

    return removed;
}

static void tuple_list_destroy(TupleList *list)
{
    Tuple *current;

    if (list == NULL) {
        return;
    }

    current = list->head;

    while (current != NULL) {
        Tuple *next = current->next;

        free(current->values);
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

static int tuple_list_print(const TupleList *list)
{
    const Tuple *tuple;

    if (list == NULL) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    tuple = list->head;

    while (tuple != NULL) {
        size_t index;

        if (putchar('(') == EOF) {
            return -1;
        }

        for (index = 0; index < tuple->length; ++index) {
            if (index > 0 && printf(", ") < 0) {
                return -1;
            }

            if (printf("%d", tuple->values[index]) < 0) {
                return -1;
            }
        }

        if (putchar(')') == EOF) {
            return -1;
        }

        tuple = tuple->next;

        if (tuple != NULL && printf(", ") < 0) {
            return -1;
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    TupleList list = {NULL, NULL};
    const int first[] = {1, 2};
    const int second[] = {3};
    int status = EXIT_SUCCESS;

    if (tuple_list_append(
            &list, first, sizeof(first) / sizeof(first[0])) != 0 ||
        tuple_list_append(&list, NULL, 0) != 0 ||
        tuple_list_append(
            &list, second, sizeof(second) / sizeof(second[0])) != 0 ||
        tuple_list_append(&list, NULL, 0) != 0) {
        fprintf(stderr, "Failed to create tuple list\n");
        tuple_list_destroy(&list);
        return EXIT_FAILURE;
    }

    remove_empty_tuples(&list);

    if (tuple_list_print(&list) != 0) {
        fprintf(stderr, "Failed to print tuple list\n");
        status = EXIT_FAILURE;
    }

    tuple_list_destroy(&list);
    return status;
}