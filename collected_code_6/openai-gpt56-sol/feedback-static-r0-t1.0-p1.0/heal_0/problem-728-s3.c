#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int sum_lists(const int *list1, const int *list2, size_t length,
                     long long *sum)
{
    size_t i;
    long long total = 0;

    if (sum == NULL || (length > 0 && (list1 == NULL || list2 == NULL))) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        total += (long long)list1[i] + (long long)list2[i];
    }

    *sum = total;
    return 0;
}

int main(void)
{
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {6, 7, 8, 9, 10};
    const size_t length = sizeof(list1) / sizeof(list1[0]);
    long long sum;

    if (length != sizeof(list2) / sizeof(list2[0])) {
        fputs("List lengths do not match.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_lists(list1, list2, length, &sum) != 0) {
        fputs("Failed to sum the lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}