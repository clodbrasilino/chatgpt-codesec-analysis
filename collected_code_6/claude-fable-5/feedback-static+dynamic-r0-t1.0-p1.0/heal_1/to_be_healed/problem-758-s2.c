#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

static bool lists_equal(const int *a, size_t len_a, const int *b, size_t len_b)
{
    size_t i;

    if (len_a != len_b) {
        return false;
    }
    for (i = 0U; i < len_a; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

static int count_unique_lists(const int *const *lists, const size_t *lengths,
                              size_t num_lists, size_t *result)
{
    size_t i;
    size_t j;
    size_t count = 0U;
    /* Possible weaknesses found:
     *  The scope of the variable 'duplicate' can be reduced. [variableScope]
     */
    bool duplicate;

    if (result == NULL) {
        return -1;
    }
    if ((num_lists > 0U) && ((lists == NULL) || (lengths == NULL))) {
        return -1;
    }
    for (i = 0U; i < num_lists; i++) {
        if ((lengths[i] > 0U) && (lists[i] == NULL)) {
            return -1;
        }
    }
    for (i = 0U; i < num_lists; i++) {
        duplicate = false;
        for (j = 0U; j < i; j++) {
            if (lists_equal(lists[i], lengths[i], lists[j], lengths[j])) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            count++;
        }
    }
    *result = count;
    return 0;
}

int main(void)
{
    static const int list1[] = {1, 2, 3};
    static const int list2[] = {4, 5};
    static const int list3[] = {1, 2, 3};
    static const int list4[] = {6, 7, 8, 9};
    static const int list5[] = {4, 5};
    const int *const lists[] = {list1, list2, list3, list4, list5};
    const size_t lengths[] = {3U, 2U, 3U, 4U, 2U};
    const size_t num_lists = sizeof(lists) / sizeof(lists[0]);
    size_t unique_count = 0U;

    if (count_unique_lists(lists, lengths, num_lists, &unique_count) != 0) {
        (void)fprintf(stderr, "Failed to count unique lists\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of unique lists: %zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}