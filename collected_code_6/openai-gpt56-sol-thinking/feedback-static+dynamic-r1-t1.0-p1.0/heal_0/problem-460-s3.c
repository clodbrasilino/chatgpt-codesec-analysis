#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool get_first_elements(
    const int *const sublists[],
    const size_t lengths[],
    size_t sublist_count,
    int first_elements[],
    size_t output_capacity)
{
    size_t i;

    if (sublist_count == 0U) {
        return true;
    }

    if (sublists == NULL || lengths == NULL || first_elements == NULL ||
        output_capacity < sublist_count) {
        return false;
    }

    for (i = 0U; i < sublist_count; ++i) {
        if (sublists[i] == NULL || lengths[i] == 0U) {
            return false;
        }
    }

    for (i = 0U; i < sublist_count; ++i) {
        first_elements[i] = sublists[i][0];
    }

    return true;
}

int main(void)
{
    const int sublist1[] = {1, 2, 3};
    const int sublist2[] = {4, 5};
    const int sublist3[] = {6, 7, 8, 9};
    const int *const sublists[] = {sublist1, sublist2, sublist3};
    const size_t lengths[] = {
        sizeof sublist1 / sizeof sublist1[0],
        sizeof sublist2 / sizeof sublist2[0],
        sizeof sublist3 / sizeof sublist3[0]
    };
    int first_elements[sizeof sublists / sizeof sublists[0]];
    const size_t count = sizeof sublists / sizeof sublists[0];
    size_t i;

    if (!get_first_elements(
            sublists,
            lengths,
            count,
            first_elements,
            sizeof first_elements / sizeof first_elements[0])) {
        if (fprintf(stderr, "Unable to get first elements.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%d%s", first_elements[i], i + 1U == count ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}