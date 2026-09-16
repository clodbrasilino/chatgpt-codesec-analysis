#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int find_triplet_with_sum(int *values, size_t count, long long target,
                                 int *first, int *second, int *third)
{
    if (values == NULL || first == NULL || second == NULL || third == NULL ||
        count < 3U) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    for (size_t i = 0U; i < count - 2U; ++i) {
        size_t left = i + 1U;
        size_t right = count - 1U;

        while (left < right) {
            const long long sum = (long long)values[i] +
                                  (long long)values[left] +
                                  (long long)values[right];

            if (sum == target) {
                *first = values[i];
                *second = values[left];
                *third = values[right];
                return 1;
            }

            if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return 0;
}

int main(void)
{
    size_t count;
    long long target;

    if (scanf("%zu", &count) != 1 || count < 3U ||
        count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%lld", &target) != 1) {
        free(values);
        return EXIT_FAILURE;
    }

    int first;
    int second;
    int third;

    if (find_triplet_with_sum(values, count, target,
                              &first, &second, &third) != 0) {
        printf("%d %d %d\n", first, second, third);
    } else {
        printf("No triplet found\n");
    }

    free(values);
    return EXIT_SUCCESS;
}