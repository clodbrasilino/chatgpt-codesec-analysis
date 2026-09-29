#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static bool is_tuple_divisible_by(const Tuple *tuple, int k)
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
        if (!is_tuple_divisible_by(&tuples[i], k)) {
            continue;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", tuples[i].elements[j]) < 0) {
                return -1;
            }
        }

        if (fputs(")\n", stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    int first[] = {6, 12, 18};
    int second[] = {4, 8, 10};
    int third[] = {9, 15, 21};
    int fourth[] = {3, 6, 27, 30};

    const Tuple tuples[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]},
        {fourth, sizeof fourth / sizeof fourth[0]}
    };

    const int k = 3;

    if (print_divisible_tuples(tuples, sizeof tuples / sizeof tuples[0], k) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}