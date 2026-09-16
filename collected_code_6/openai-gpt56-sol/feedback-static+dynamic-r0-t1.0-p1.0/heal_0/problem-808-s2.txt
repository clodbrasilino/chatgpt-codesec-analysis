#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

static bool tuples_contain_k(const Tuple *tuples, size_t tuple_count, int k)
{
    if (tuples == NULL && tuple_count != 0U) {
        return false;
    }

    for (size_t i = 0U; i < tuple_count; ++i) {
        if (tuples[i].values == NULL && tuples[i].length != 0U) {
            continue;
        }

        for (size_t j = 0U; j < tuples[i].length; ++j) {
            if (tuples[i].values[j] == k) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    int first[] = {1, 2, 3};
    int second[] = {4, 5, 6};
    int third[] = {7, 8, 9};

    Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    int k = 0;

    if (printf("Enter k: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &k) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    const bool found = tuples_contain_k(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        k
    );

    if (printf("%s\n", found ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}