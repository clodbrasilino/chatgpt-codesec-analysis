#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

static int compare_strings(const void *lhs, const void *rhs)
{
    const char *const *left = lhs;
    const char *const *right = rhs;
    return strcmp(*left, *right);
}

static int sort_sublists(StringList *lists, size_t list_count)
{
    if (lists == NULL && list_count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (lists[i].items == NULL && lists[i].count != 0U) {
            return -1;
        }

        for (size_t j = 0U; j < lists[i].count; ++j) {
            if (lists[i].items[j] == NULL) {
                return -1;
            }
        }

        if (lists[i].count > 1U) {
            qsort(lists[i].items, lists[i].count,
                  sizeof(lists[i].items[0]), compare_strings);
        }
    }

    return 0;
}

static int print_sublists(const StringList *lists, size_t list_count)
{
    if (lists == NULL && list_count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (lists[i].items == NULL && lists[i].count != 0U) {
            return -1;
        }

        printf("[");
        for (size_t j = 0U; j < lists[i].count; ++j) {
            if (lists[i].items[j] == NULL) {
                return -1;
            }

            printf("%s%s", lists[i].items[j],
                   j + 1U < lists[i].count ? ", " : "");
        }
        printf("]\n");
    }

    if (ferror(stdout)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char *first[] = {"pear", "apple", "orange"};
    char *second[] = {"zebra", "ant", "lion", "bear"};
    char *third[] = {"blue", "red", "green"};

    StringList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    size_t list_count = sizeof(lists) / sizeof(lists[0]);

    if (sort_sublists(lists, list_count) != 0) {
        fprintf(stderr, "Failed to sort the sublists.\n");
        return EXIT_FAILURE;
    }

    if (print_sublists(lists, list_count) != 0) {
        fprintf(stderr, "Failed to print the sublists.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}