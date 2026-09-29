#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t length;
} Sublist;

typedef struct {
    Sublist *sublists;
    size_t count;
} ListOfLists;

static void destroy_list(ListOfLists *list)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (list == NULL) {
        return;
    }

    if (list->sublists != NULL) {
        for (i = 0; i < list->count; ++i) {
            free(list->sublists[i].values);
        }
        free(list->sublists);
    }

    list->sublists = NULL;
    list->count = 0;
}

static bool create_list(ListOfLists *list,
                        const int *const source[],
                        const size_t lengths[],
                        size_t count)
{
    size_t i;

    if (list == NULL) {
        return false;
    }

    list->sublists = NULL;
    list->count = 0;

    if (count == 0) {
        return true;
    }

    if (source == NULL || lengths == NULL ||
        count > SIZE_MAX / sizeof(*list->sublists)) {
        return false;
    }

    list->sublists = calloc(count, sizeof(*list->sublists));
    if (list->sublists == NULL) {
        return false;
    }

    list->count = count;

    for (i = 0; i < count; ++i) {
        if (lengths[i] == 0) {
            continue;
        }

        if (source[i] == NULL ||
            lengths[i] > SIZE_MAX / sizeof(*list->sublists[i].values)) {
            destroy_list(list);
            return false;
        }

        list->sublists[i].values =
            malloc(lengths[i] * sizeof(*list->sublists[i].values));

        if (list->sublists[i].values == NULL) {
            destroy_list(list);
            return false;
        }

        memcpy(list->sublists[i].values,
               source[i],
               lengths[i] * sizeof(*list->sublists[i].values));

        list->sublists[i].length = lengths[i];
    }

    return true;
}

static bool remove_sublists_outside_range(ListOfLists *list,
                                          size_t first_index,
                                          size_t last_index)
{
    size_t old_count;
    size_t last_kept;
    size_t kept_count;
    size_t i;
    Sublist *resized;

    if (list == NULL || first_index > last_index) {
        return false;
    }

    if (list->count == 0) {
        return list->sublists == NULL;
    }

    if (list->sublists == NULL ||
        list->count > SIZE_MAX / sizeof(*list->sublists)) {
        return false;
    }

    for (i = 0; i < list->count; ++i) {
        if (list->sublists[i].length != 0 &&
            list->sublists[i].values == NULL) {
            return false;
        }
    }

    old_count = list->count;

    if (first_index >= old_count) {
        destroy_list(list);
        return true;
    }

    last_kept = last_index < old_count - 1 ? last_index : old_count - 1;
    kept_count = last_kept - first_index + 1;

    for (i = 0; i < first_index; ++i) {
        free(list->sublists[i].values);
        list->sublists[i].values = NULL;
        list->sublists[i].length = 0;
    }

    for (i = last_kept + 1; i < old_count; ++i) {
        free(list->sublists[i].values);
        list->sublists[i].values = NULL;
        list->sublists[i].length = 0;
    }

    if (first_index != 0) {
        memmove(list->sublists,
                list->sublists + first_index,
                kept_count * sizeof(*list->sublists));
    }

    for (i = kept_count; i < old_count; ++i) {
        list->sublists[i].values = NULL;
        list->sublists[i].length = 0;
    }

    list->count = kept_count;

    resized = realloc(list->sublists,
                      kept_count * sizeof(*list->sublists));
    if (resized != NULL) {
        list->sublists = resized;
    }

    return true;
}

static bool print_list(const ListOfLists *list)
{
    size_t i;
    size_t j;

    if (list == NULL ||
        (list->count != 0 && list->sublists == NULL)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (i = 0; i < list->count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (putchar('[') == EOF) {
            return false;
        }

        for (j = 0; j < list->sublists[i].length; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", list->sublists[i].values[j]) < 0) {
                return false;
            }
        }

        if (putchar(']') == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6};
    const int fourth[] = {7, 8, 9};
    const int *const source[] = {first, second, third, fourth};
    const size_t lengths[] = {3, 2, 1, 3};
    ListOfLists list = {NULL, 0};
    int status = EXIT_SUCCESS;

    if (!create_list(&list, source, lengths, 4)) {
        return EXIT_FAILURE;
    }

    if (!remove_sublists_outside_range(&list, 1, 2) ||
        !print_list(&list) ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    destroy_list(&list);
    return status;
}