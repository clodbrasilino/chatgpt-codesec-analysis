#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_lists(const int *list1, const int *list2, size_t length, long long **result)
{
    size_t i;
    long long *sums;

    if (result == NULL || (length > 0U && (list1 == NULL || list2 == NULL))) {
        return -1;
    }

    *result = NULL;

    if (length == 0U) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        sums[i] = (long long)list1[i] + (long long)list2[i];
    }

    *result = sums;
    return 0;
}

int main(void)
{
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {6, 7, 8, 9, 10};
    const size_t length = sizeof(list1) / sizeof(list1[0]);
    long long *result = NULL;
    size_t i;

    if (length != sizeof(list2) / sizeof(list2[0])) {
        fputs("List lengths do not match.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_lists(list1, list2, length, &result) != 0) {
        fputs("Unable to sum lists.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; ++i) {
        if (printf("%lld%s", result[i], i + 1U == length ? "\n" : " ") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}