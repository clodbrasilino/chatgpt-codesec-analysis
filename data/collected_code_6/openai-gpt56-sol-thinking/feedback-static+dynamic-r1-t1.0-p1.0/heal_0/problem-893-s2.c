#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool get_last_elements(const int *const sublists[],
                              const size_t lengths[],
                              size_t count,
                              int results[])
{
    if (count == 0U) {
        return true;
    }

    if (sublists == NULL || lengths == NULL || results == NULL) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (sublists[i] == NULL || lengths[i] == 0U) {
            return false;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        results[i] = sublists[i][lengths[i] - 1U];
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};

    const int *const sublists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof first / sizeof first[0],
        sizeof second / sizeof second[0],
        sizeof third / sizeof third[0]
    };
    int results[sizeof sublists / sizeof sublists[0]];
    const size_t count = sizeof sublists / sizeof sublists[0];

    if (!get_last_elements(sublists, lengths, count, results)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%d%s", results[i], i + 1U == count ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}