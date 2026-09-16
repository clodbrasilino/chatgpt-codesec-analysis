#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

static void free_lists(IntList *lists, size_t count)
{
    if (lists == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(lists[i].items);
    }

    free(lists);
}

static int merge_first_and_last(const IntList *lists, size_t count,
                                IntList *firsts, IntList *lasts)
{
    if (lists == NULL || count == 0 || firsts == NULL || lasts == NULL) {
        return 0;
    }

    firsts->items = NULL;
    firsts->length = 0;
    lasts->items = NULL;
    lasts->length = 0;

    if (count > SIZE_MAX / sizeof(*firsts->items)) {
        return 0;
    }

    firsts->items = malloc(count * sizeof(*firsts->items));
    lasts->items = malloc(count * sizeof(*lasts->items));

    if (firsts->items == NULL || lasts->items == NULL) {
        free(firsts->items);
        free(lasts->items);
        firsts->items = NULL;
        lasts->items = NULL;
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (lists[i].items == NULL || lists[i].length == 0) {
            free(firsts->items);
            free(lasts->items);
            firsts->items = NULL;
            lasts->items = NULL;
            return 0;
        }

        firsts->items[i] = lists[i].items[0];
        lasts->items[i] = lists[i].items[lists[i].length - 1];
    }

    firsts->length = count;
    lasts->length = count;
    return 1;
}

static int read_lists(IntList **result, size_t *count)
{
    size_t list_count;
    IntList *lists;

    if (result == NULL || count == NULL || scanf("%zu", &list_count) != 1 ||
        list_count == 0 || list_count > SIZE_MAX / sizeof(*lists)) {
        return 0;
    }

    lists = calloc(list_count, sizeof(*lists));
    if (lists == NULL) {
        return 0;
    }

    for (size_t i = 0; i < list_count; ++i) {
        size_t length;

        if (scanf("%zu", &length) != 1 || length == 0 ||
            length > SIZE_MAX / sizeof(*lists[i].items)) {
            free_lists(lists, list_count);
            return 0;
        }

        lists[i].items = malloc(length * sizeof(*lists[i].items));
        if (lists[i].items == NULL) {
            free_lists(lists, list_count);
            return 0;
        }

        lists[i].length = length;

        for (size_t j = 0; j < length; ++j) {
            if (scanf("%d", &lists[i].items[j]) != 1) {
                free_lists(lists, list_count);
                return 0;
            }
        }
    }

    *result = lists;
    *count = list_count;
    return 1;
}

static void print_list(const IntList *list)
{
    for (size_t i = 0; i < list->length; ++i) {
        if (i != 0) {
            putchar(' ');
        }
        printf("%d", list->items[i]);
    }
    putchar('\n');
}

int main(void)
{
    IntList *lists = NULL;
    IntList firsts = {NULL, 0};
    IntList lasts = {NULL, 0};
    size_t count = 0;
    int status = EXIT_FAILURE;

    if (!read_lists(&lists, &count)) {
        fprintf(stderr, "Invalid input or allocation failure\n");
        goto cleanup;
    }

    if (!merge_first_and_last(lists, count, &firsts, &lasts)) {
        fprintf(stderr, "Unable to merge lists\n");
        goto cleanup;
    }

    print_list(&firsts);
    print_list(&lasts);
    status = EXIT_SUCCESS;

cleanup:
    free(firsts.items);
    free(lasts.items);
    free_lists(lists, count);
    return status;
}