#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains(const int *list, size_t length, int value)
{
    for (size_t i = 0; i < length; ++i) {
        if (list[i] == value) {
            return true;
        }
    }

    return false;
}

static int find_common_elements(
    const int *first,
    size_t first_length,
    const int *second,
    size_t second_length,
    const int *third,
    size_t third_length,
    int *result,
    size_t result_capacity,
    size_t *result_length)
{
    if (result_length == NULL ||
        (first == NULL && first_length != 0U) ||
        (second == NULL && second_length != 0U) ||
        (third == NULL && third_length != 0U) ||
        (result == NULL && result_capacity != 0U)) {
        return EINVAL;
    }

    *result_length = 0U;

    for (size_t i = 0; i < first_length; ++i) {
        if (contains(first, i, first[i])) {
            continue;
        }

        if (contains(second, second_length, first[i]) &&
            contains(third, third_length, first[i])) {
            if (*result_length >= result_capacity) {
                return ENOSPC;
            }

            result[*result_length] = first[i];
            ++(*result_length);
        }
    }

    return 0;
}

int main(void)
{
    const int first[] = {1, 5, 10, 20, 40, 80};
    const int second[] = {6, 7, 20, 80, 100};
    const int third[] = {3, 4, 15, 20, 30, 70, 80};
    int common[sizeof(first) / sizeof(first[0])];
    size_t common_length = 0U;

    int status = find_common_elements(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        third,
        sizeof(third) / sizeof(third[0]),
        common,
        sizeof(common) / sizeof(common[0]),
        &common_length);

    if (status != 0) {
        if (fprintf(stderr, "Unable to find common elements: error %d\n", status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fputs("Common elements:", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < common_length; ++i) {
        if (printf(" %d", common[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}