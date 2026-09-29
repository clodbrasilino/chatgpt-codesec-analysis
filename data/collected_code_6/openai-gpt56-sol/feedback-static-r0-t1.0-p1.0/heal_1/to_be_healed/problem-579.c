#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *values, size_t count, int target)
{
    for (size_t i = 0; i < count; ++i) {
        if (values[i] == target) {
            return true;
        }
    }
    return false;
}

static int *find_dissimilar(const int *first, size_t first_count,
                            const int *second, size_t second_count,
                            size_t *result_count)
{
    if (result_count == NULL ||
        (first == NULL && first_count != 0U) ||
        (second == NULL && second_count != 0U) ||
        first_count > SIZE_MAX - second_count) {
        return NULL;
    }

    *result_count = 0U;
    size_t capacity = first_count + second_count;

    if (capacity == 0U) {
        return NULL;
    }

    int *result = malloc(capacity * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < first_count; ++i) {
        if (!contains(second, second_count, first[i]) &&
            !contains(result, *result_count, first[i])) {
            result[(*result_count)++] = first[i];
        }
    }

    for (size_t i = 0U; i < second_count; ++i) {
        if (!contains(first, first_count, second[i]) &&
            !contains(result, *result_count, second[i])) {
            result[(*result_count)++] = second[i];
        }
    }

    return result;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {4, 5, 6, 7, 8};
    const size_t first_count = sizeof(first) / sizeof(first[0]);
    const size_t second_count = sizeof(second) / sizeof(second[0]);
    size_t result_count = 0U;

    int *result = find_dissimilar(first, first_count, second, second_count,
                                  &result_count);

    /* Possible weaknesses found:
     *  Condition 'first_count+second_count!=0U' is always true [knownConditionTrueFalse]
     */
    if (result == NULL && first_count + second_count != 0U) {
        fputs("Unable to compute dissimilar elements.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Dissimilar elements: ");
    for (size_t i = 0U; i < result_count; ++i) {
        printf("%d%s", result[i], i + 1U < result_count ? " " : "\n");
    }

    if (result_count == 0U) {
        putchar('\n');
    }

    free(result);
    return EXIT_SUCCESS;
}