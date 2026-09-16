#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool count_sublists_containing(const int *const sublists[],
                               const size_t lengths[],
                               size_t sublist_count,
                               int target,
                               size_t *result)
{
    size_t count = 0;

    if (result == NULL) {
        return false;
    }

    *result = 0;

    if (sublist_count > 0 && (sublists == NULL || lengths == NULL)) {
        return false;
    }

    for (size_t i = 0; i < sublist_count; ++i) {
        if (lengths[i] > 0 && sublists[i] == NULL) {
            return false;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            if (sublists[i][j] == target) {
                ++count;
                break;
            }
        }
    }

    *result = count;
    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {2, 7, 8};
    const int fourth[] = {9, 2, 2};

    const int *const sublists[] = {
        first,
        second,
        third,
        fourth
    };

    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0]),
        sizeof(fourth) / sizeof(fourth[0])
    };

    const size_t sublist_count = sizeof(sublists) / sizeof(sublists[0]);
    size_t result = 0;

    if (!count_sublists_containing(sublists, lengths, sublist_count, 2, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}