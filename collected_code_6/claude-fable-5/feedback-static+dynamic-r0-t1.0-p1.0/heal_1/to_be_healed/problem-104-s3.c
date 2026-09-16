#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return strcmp(*sa, *sb);
}

static int sort_sublists(char ***lists, const size_t *sizes, size_t num_lists)
{
    size_t i;

    if (lists == NULL || sizes == NULL) {
        return -1;
    }

    for (i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            return -1;
        }
        if (sizes[i] > 1) {
            qsort(lists[i], sizes[i], sizeof(char *), compare_strings);
        }
    }

    return 0;
}

static void print_lists(char ***lists, const size_t *sizes, size_t num_lists)
{
    size_t i;
    size_t j;

    for (i = 0; i < num_lists; i++) {
        printf("[");
        for (j = 0; j < sizes[i]; j++) {
            printf("%s", lists[i][j]);
            if (j + 1 < sizes[i]) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    char *list1[] = { "banana", "apple", "cherry" };
    char *list2[] = { "delta", "alpha", "charlie", "bravo" };
    char *list3[] = { "zebra", "yak" };
    char **lists[] = { list1, list2, list3 };
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    size_t sizes[] = { 3, 4, 2 };
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    if (sort_sublists(lists, sizes, num_lists) != 0) {
        fprintf(stderr, "Error: invalid input to sort_sublists\n");
        return EXIT_FAILURE;
    }

    print_lists(lists, sizes, num_lists);

    return EXIT_SUCCESS;
}