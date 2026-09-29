#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static bool all_elements_divisible(const Tuple *tuple, int k)
{
    if (tuple == NULL || k == 0 || (tuple->length > 0 && tuple->elements == NULL)) {
        return false;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->elements[i] % k != 0) {
            return false;
        }
    }

    return true;
}

static int print_divisible_tuples(const Tuple *tuples, size_t count, int k)
{
    if ((count > 0 && tuples == NULL) || k == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (all_elements_divisible(&tuples[i], k)) {
            putchar('(');
            for (size_t j = 0; j < tuples[i].length; ++j) {
                if (j > 0) {
                    fputs(", ", stdout);
                }
                if (printf("%d", tuples[i].elements[j]) < 0) {
                    return -1;
                }
            }
            if (puts(")") == EOF) {
                return -1;
            }
        }
    }

    return ferror(stdout) ? -1 : 0;
}

int main(void)
{
    int first[] = {2, 4, 6};
    int second[] = {3, 6, 9};
    int third[] = {8, 12, 16};
    int fourth[] = {5, 10, 15};

    Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };

    int k = 2;

    if (print_divisible_tuples(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            k) != 0) {
        fputs("Failed to process tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}