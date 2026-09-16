#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_lists(const int *first, const int *second, size_t length,
                     int64_t **result)
{
    int64_t *sums = NULL;
    size_t i;

    if (result == NULL || (length > 0U && (first == NULL || second == NULL))) {
        return EINVAL;
    }

    *result = NULL;

    if (length == 0U) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sums)) {
        return EOVERFLOW;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return ENOMEM;
    }

    for (i = 0U; i < length; ++i) {
        sums[i] = (int64_t)first[i] + (int64_t)second[i];
    }

    *result = sums;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {5, 4, 3, 2, 1};
    const size_t length = sizeof(first) / sizeof(first[0]);
    int64_t *sums = NULL;
    int status;
    size_t i;

    if (length != sizeof(second) / sizeof(second[0])) {
        fputs("List lengths do not match.\n", stderr);
        return EXIT_FAILURE;
    }

    status = sum_lists(first, second, length, &sums);
    if (status != 0) {
        errno = status;
        perror("sum_lists");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; ++i) {
        if (printf("%lld%s", (long long)sums[i],
                   (i + 1U == length) ? "\n" : " ") < 0) {
            free(sums);
            return EXIT_FAILURE;
        }
    }

    free(sums);
    return EXIT_SUCCESS;
}