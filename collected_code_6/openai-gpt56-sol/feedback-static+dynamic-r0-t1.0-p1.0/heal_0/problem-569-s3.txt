#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

static int compare_strings(const void *left, const void *right)
{
    const char *const *a = left;
    const char *const *b = right;

    return strcmp(*a, *b);
}

static int sort_sublists(StringList *lists, size_t list_count)
{
    if (list_count > 0 && lists == NULL) {
        return -1;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].count > 0 && lists[i].items == NULL) {
            return -1;
        }

        for (size_t j = 0; j < lists[i].count; ++j) {
            if (lists[i].items[j] == NULL) {
                return -1;
            }
        }

        if (lists[i].count > 1) {
            qsort(lists[i].items, lists[i].count,
                  sizeof(lists[i].items[0]), compare_strings);
        }
    }

    return 0;
}

static int print_sublists(const StringList *lists, size_t list_count)
{
    if (list_count > 0 && lists == NULL) {
        return -1;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].count > 0 && lists[i].items == NULL) {
            return -1;
        }

        printf("[");
        for (size_t j = 0; j < lists[i].count; ++j) {
            if (lists[i].items[j] == NULL) {
                return -1;
            }

            printf("%s%s", lists[i].items[j],
                   j + 1 < lists[i].count ? ", " : "");
        }
        printf("]\n");
    }

    return ferror(stdout) ? -1 : 0;
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
        fputs("Failed to sort sublists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_sublists(lists, list_count) != 0) {
        fputs("Failed to print sublists.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}