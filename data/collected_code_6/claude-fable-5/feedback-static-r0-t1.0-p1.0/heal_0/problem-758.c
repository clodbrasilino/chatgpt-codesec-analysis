#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool lists_equal(const int *a, size_t a_len, const int *b, size_t b_len)
{
    size_t i;

    if (a_len != b_len) {
        return false;
    }
    for (i = 0; i < a_len; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

static int count_unique_lists(const int **lists, const size_t *lengths, size_t num_lists, size_t *result)
{
    size_t i;
    size_t j;
    size_t unique_count;
    bool *is_duplicate;

    if (result == NULL) {
        return -1;
    }
    if (num_lists == 0) {
        *result = 0;
        return 0;
    }
    if (lists == NULL || lengths == NULL) {
        return -1;
    }

    is_duplicate = calloc(num_lists, sizeof(bool));
    if (is_duplicate == NULL) {
        return -1;
    }

    unique_count = 0;
    for (i = 0; i < num_lists; i++) {
        if (is_duplicate[i]) {
            continue;
        }
        unique_count++;
        for (j = i + 1; j < num_lists; j++) {
            if (!is_duplicate[j] && lists_equal(lists[i], lengths[i], lists[j], lengths[j])) {
                is_duplicate[j] = true;
            }
        }
    }

    free(is_duplicate);
    *result = unique_count;
    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {1, 2, 3};
    int list4[] = {6, 7, 8, 9};
    int list5[] = {4, 5};

    const int *lists[] = {list1, list2, list3, list4, list5};
    const size_t lengths[] = {3, 2, 3, 4, 2};
    const size_t num_lists = sizeof(lists) / sizeof(lists[0]);
    size_t unique;

    if (count_unique_lists(lists, lengths, num_lists, &unique) != 0) {
        fprintf(stderr, "Failed to count unique lists\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of unique lists: %zu\n", unique) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}