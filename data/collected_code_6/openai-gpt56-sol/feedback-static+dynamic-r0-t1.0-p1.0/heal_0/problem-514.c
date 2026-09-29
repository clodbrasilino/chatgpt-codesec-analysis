#include <stdio.h>
#include <stddef.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

int sum_tuple_elements(const Tuple *tuples, size_t tuple_count, long long *result)
{
    size_t i;
    size_t j;
    long long sum = 0;

    if (result == NULL || (tuple_count > 0 && tuples == NULL)) {
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (tuples[i].length > 0 && tuples[i].elements == NULL) {
            return -1;
        }

        for (j = 0; j < tuples[i].length; ++j) {
            sum += tuples[i].elements[j];
        }
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    long long sum;

    if (sum_tuple_elements(tuples, sizeof(tuples) / sizeof(tuples[0]), &sum) != 0) {
        fputs("Failed to sum tuple elements.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", sum) < 0) {
        return 1;
    }

    return 0;
}