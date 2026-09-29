#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    long long sum;
} Pair;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_k_pairs(const int *first, size_t first_count,
                        const int *second, size_t second_count,
                        size_t k, Pair *pairs)
{
    int *sorted_first = NULL;
    int *sorted_second = NULL;
    size_t i = 0U;
    size_t j = 0U;
    size_t count = 0U;

    if (first == NULL || second == NULL || pairs == NULL ||
        first_count == 0U || second_count == 0U ||
        first_count > SIZE_MAX / sizeof(*sorted_first) ||
        second_count > SIZE_MAX / sizeof(*sorted_second)) {
        return -1;
    }

    sorted_first = malloc(first_count * sizeof(*sorted_first));
    sorted_second = malloc(second_count * sizeof(*sorted_second));
    if (sorted_first == NULL || sorted_second == NULL) {
        free(sorted_first);
        free(sorted_second);
        return -1;
    }

    for (i = 0U; i < first_count; ++i) {
        sorted_first[i] = first[i];
    }

    for (i = 0U; i < second_count; ++i) {
        sorted_second[i] = second[i];
    }

    qsort(sorted_first, first_count, sizeof(*sorted_first), compare_ints);
    qsort(sorted_second, second_count, sizeof(*sorted_second), compare_ints);

    i = 0U;
    j = 0U;

    while (count < k && i < first_count) {
        pairs[count].first = sorted_first[i];
        pairs[count].second = sorted_second[j];
        pairs[count].sum = (long long)sorted_first[i] + sorted_second[j];
        ++count;
        ++j;

        if (j == second_count) {
            j = 0U;
            ++i;
        }
    }

    free(sorted_first);
    free(sorted_second);

    return count == k ? 0 : -1;
}

static int read_size(const char *prompt, size_t *value)
{
    unsigned long long input;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (printf("%s", prompt) < 0 || fflush(stdout) == EOF) {
        return -1;
    }

    errno = 0;
    if (scanf("%llu", &input) != 1 || errno == ERANGE || input > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

static int read_array(const char *prompt, int *array, size_t count)
{
    size_t i;

    if (prompt == NULL || array == NULL) {
        return -1;
    }

    if (printf("%s", prompt) < 0 || fflush(stdout) == EOF) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    int *first = NULL;
    int *second = NULL;
    Pair *pairs = NULL;
    size_t first_count;
    size_t second_count;
    size_t k;
    size_t i;
    int status = EXIT_FAILURE;

    if (read_size("First array size: ", &first_count) != 0 ||
        read_size("Second array size: ", &second_count) != 0 ||
        read_size("Number of pairs: ", &k) != 0 ||
        first_count == 0U || second_count == 0U || k == 0U ||
        first_count > SIZE_MAX / second_count ||
        k > first_count * second_count ||
        first_count > SIZE_MAX / sizeof(*first) ||
        second_count > SIZE_MAX / sizeof(*second) ||
        k > SIZE_MAX / sizeof(*pairs)) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    first = malloc(first_count * sizeof(*first));
    second = malloc(second_count * sizeof(*second));
    pairs = malloc(k * sizeof(*pairs));

    if (first == NULL || second == NULL || pairs == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        goto cleanup;
    }

    if (read_array("First array elements: ", first, first_count) != 0 ||
        read_array("Second array elements: ", second, second_count) != 0) {
        fputs("Invalid array input.\n", stderr);
        goto cleanup;
    }

    if (find_k_pairs(first, first_count, second, second_count, k, pairs) != 0) {
        fputs("Unable to find the requested pairs.\n", stderr);
        goto cleanup;
    }

    for (i = 0U; i < k; ++i) {
        if (printf("(%d, %d), sum = %lld\n",
                   pairs[i].first, pairs[i].second, pairs[i].sum) < 0) {
            fputs("Output error.\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(pairs);
    free(second);
    free(first);
    return status;
}