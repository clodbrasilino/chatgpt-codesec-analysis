#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    int second;
} Tuple;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool find_common_first(const Tuple *tuples, size_t count, int *result)
{
    if (tuples == NULL || result == NULL || count < 2U) {
        return false;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return false;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        values[i] = tuples[i].first;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    bool found = false;

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] == values[i - 1U]) {
            *result = values[i];
            found = true;
            break;
        }
    }

    free(values);
    return found;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 30},
        {2, 40}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int common_first = 0;

    if (find_common_first(tuples, count, &common_first)) {
        if (printf("%d\n", common_first) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No common first element\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}