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
    if ((lists == NULL || sizes == NULL) && list_count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (sizes[i] != 0U && lists[i] == NULL) {
            return -1;
        }

        for (size_t j = 0U; j < sizes[i]; ++j) {
            if (lists[i][j] == NULL) {
                return -1;
            }
        }
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (sizes[i] > 1U) {
            qsort(lists[i], sizes[i], sizeof lists[i][0], compare_strings);
        }
    }

    return 0;
}

static int print_sublists(char ***lists, const size_t *sizes, size_t list_count)
{
    if ((lists == NULL || sizes == NULL) && list_count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (sizes[i] != 0U && lists[i] == NULL) {
            return -1;
        }

        for (size_t j = 0U; j < sizes[i]; ++j) {
            if (lists[i][j] == NULL) {
                return -1;
            }

            if (printf("%s%s", lists[i][j],
                       j + 1U == sizes[i] ? "\n" : " ") < 0) {
                return -1;
            }
        }

        if (sizes[i] == 0U && putchar('\n') == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    char *first[] = {"pear", "apple", "orange"};
    char *second[] = {"zebra", "ant", "lion", "bear"};
    char *third[] = {"blue", "red", "green"};
    char **lists[] = {first, second, third};
    const size_t sizes[] = {
        sizeof first / sizeof first[0],
        sizeof second / sizeof second[0],
        sizeof third / sizeof third[0]
    };
    const size_t list_count = sizeof lists / sizeof lists[0];

    if (sort_sublists(lists, sizes, list_count) != 0) {
        fputs("Failed to sort the sublists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_sublists(lists, sizes, list_count) != 0) {
        fputs("Failed to print the sublists.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}