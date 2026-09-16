#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = a;
    const char *const *sb = b;
    return strcmp(*sa, *sb);
}

static int sort_sublist(const char **sublist, size_t count)
{
    if (sublist == NULL) {
        return -1;
    }
    if (count > 1) {
        qsort(sublist, count, sizeof(const char *), compare_strings);
    }
    return 0;
}

static int sort_list_of_lists(const char ***lists, const size_t *counts, size_t num_lists)
{
    size_t i;

    if (lists == NULL || counts == NULL) {
        return -1;
    }
    for (i = 0; i < num_lists; i++) {
        if (sort_sublist(lists[i], counts[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

static void print_list_of_lists(const char ***lists, const size_t *counts, size_t num_lists)
{
    size_t i;
    size_t j;

    for (i = 0; i < num_lists; i++) {
        printf("Sublist %zu: ", i);
        for (j = 0; j < counts[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    const char *sublist1[] = { "banana", "apple", "cherry" };
    const char *sublist2[] = { "zebra", "mango", "kiwi", "apricot" };
    const char *sublist3[] = { "pear" };

    const char **lists[] = { sublist1, sublist2, sublist3 };
    size_t counts[] = { 3, 4, 1 };
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    printf("Before sorting:\n");
    print_list_of_lists(lists, counts, num_lists);

    if (sort_list_of_lists(lists, counts, num_lists) != 0) {
        fprintf(stderr, "Error: failed to sort list of lists\n");
        return EXIT_FAILURE;
    }

    printf("After sorting:\n");
    print_list_of_lists(lists, counts, num_lists);

    return EXIT_SUCCESS;
}