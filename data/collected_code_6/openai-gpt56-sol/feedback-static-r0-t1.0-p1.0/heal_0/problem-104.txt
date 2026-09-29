#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_strings(const void *left, const void *right)
{
    const char *const *a = left;
    const char *const *b = right;

    return strcmp(*a, *b);
}

static int sort_sublists(char ***lists, const size_t *sizes, size_t list_count)
{
    size_t i;

    if ((list_count > 0U && (lists == NULL || sizes == NULL))) {
        return -1;
    }

    for (i = 0U; i < list_count; ++i) {
        if (sizes[i] > 0U && lists[i] == NULL) {
            return -1;
        }

        for (size_t j = 0U; j < sizes[i]; ++j) {
            if (lists[i][j] == NULL) {
                return -1;
            }
        }
    }

    for (i = 0U; i < list_count; ++i) {
        if (sizes[i] > 1U) {
            qsort(lists[i], sizes[i], sizeof(lists[i][0]), compare_strings);
        }
    }

    return 0;
}

static int print_sublists(char *const *const *lists,
                          const size_t *sizes,
                          size_t list_count)
{
    size_t i;

    if (list_count > 0U && (lists == NULL || sizes == NULL)) {
        return -1;
    }

    for (i = 0U; i < list_count; ++i) {
        size_t j;

        if (sizes[i] > 0U && lists[i] == NULL) {
            return -1;
        }

        printf("[");
        for (j = 0U; j < sizes[i]; ++j) {
            if (lists[i][j] == NULL) {
                return -1;
            }

            printf("%s%s", lists[i][j], j + 1U < sizes[i] ? ", " : "");
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
    char **lists[] = {first, second, third};
    const size_t sizes[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);

    if (sort_sublists(lists, sizes, list_count) != 0) {
        fprintf(stderr, "Failed to sort sublists.\n");
        return EXIT_FAILURE;
    }

    if (print_sublists(lists, sizes, list_count) != 0) {
        fprintf(stderr, "Failed to print sublists.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}