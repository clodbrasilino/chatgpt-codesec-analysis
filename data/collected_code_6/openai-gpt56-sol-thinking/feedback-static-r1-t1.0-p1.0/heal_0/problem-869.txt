#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sublist {
    int *values;
    size_t length;
    struct Sublist *next;
} Sublist;

static Sublist *create_sublist(const int *values, size_t length)
{
    Sublist *sublist;

    if ((values == NULL && length != 0U) ||
        length > SIZE_MAX / sizeof(*values)) {
        return NULL;
    }

    sublist = malloc(sizeof(*sublist));
    if (sublist == NULL) {
        return NULL;
    }

    sublist->values = NULL;
    sublist->length = length;
    sublist->next = NULL;

    if (length != 0U) {
        sublist->values = malloc(length * sizeof(*sublist->values));
        if (sublist->values == NULL) {
            free(sublist);
            return NULL;
        }

        memcpy(sublist->values, values,
               length * sizeof(*sublist->values));
    }

    return sublist;
}

static bool append_sublist(Sublist **head, Sublist **tail,
                           const int *values, size_t length)
{
    Sublist *sublist;

    if (head == NULL || tail == NULL) {
        return false;
    }

    sublist = create_sublist(values, length);
    if (sublist == NULL) {
        return false;
    }

    if (*tail == NULL) {
        *head = sublist;
    } else {
        (*tail)->next = sublist;
    }

    *tail = sublist;
    return true;
}

static void free_sublist(Sublist *sublist)
{
    if (sublist != NULL) {
        free(sublist->values);
        free(sublist);
    }
}

static void free_list(Sublist *head)
{
    while (head != NULL) {
        Sublist *next = head->next;
        free_sublist(head);
        head = next;
    }
}

static bool sublist_is_within_range(const Sublist *sublist,
                                    int lower, int upper)
{
    size_t i;

    for (i = 0U; i < sublist->length; ++i) {
        if (sublist->values[i] < lower ||
            sublist->values[i] > upper) {
            return false;
        }
    }

    return true;
}

static bool remove_sublists_outside_range(Sublist **head,
                                          int lower, int upper)
{
    Sublist **current;

    if (head == NULL || lower > upper) {
        return false;
    }

    current = head;

    while (*current != NULL) {
        if (!sublist_is_within_range(*current, lower, upper)) {
            Sublist *removed = *current;
            *current = removed->next;
            removed->next = NULL;
            free_sublist(removed);
        } else {
            current = &(*current)->next;
        }
    }

    return true;
}

static bool print_list(const Sublist *head)
{
    const Sublist *sublist;
    bool first_sublist = true;

    if (putchar('[') == EOF) {
        return false;
    }

    for (sublist = head; sublist != NULL; sublist = sublist->next) {
        size_t i;

        if (!first_sublist && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (putchar('[') == EOF) {
            return false;
        }

        for (i = 0U; i < sublist->length; ++i) {
            if (i != 0U && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", sublist->values[i]) < 0) {
                return false;
            }
        }

        if (putchar(']') == EOF) {
            return false;
        }

        first_sublist = false;
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int values1[] = {1, 2, 3};
    const int values2[] = {-1, 2, 4};
    const int values3[] = {4, 5};
    const int values4[] = {6, 7};
    Sublist *list = NULL;
    Sublist *tail = NULL;
    int status = EXIT_SUCCESS;

    if (!append_sublist(&list, &tail, values1,
                        sizeof(values1) / sizeof(values1[0])) ||
        !append_sublist(&list, &tail, values2,
                        sizeof(values2) / sizeof(values2[0])) ||
        !append_sublist(&list, &tail, values3,
                        sizeof(values3) / sizeof(values3[0])) ||
        !append_sublist(&list, &tail, values4,
                        sizeof(values4) / sizeof(values4[0]))) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!remove_sublists_outside_range(&list, 1, 5)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!print_list(list)) {
        status = EXIT_FAILURE;
    }

cleanup:
    free_list(list);
    return status;
}