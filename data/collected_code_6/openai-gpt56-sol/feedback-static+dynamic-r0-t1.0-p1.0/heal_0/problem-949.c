#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t count;
    size_t original_index;
} Tuple;

static size_t digit_count(int value)
{
    int64_t number = value;
    size_t count = 0;

    if (number < 0) {
        number = -number;
    }

    do {
        ++count;
        number /= 10;
    } while (number != 0);

    return count;
}

static size_t tuple_digit_count(const Tuple *tuple)
{
    size_t total = 0;

    for (size_t i = 0; i < tuple->count; ++i) {
        total += digit_count(tuple->values[i]);
    }

    return total;
}

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    const size_t a_digits = tuple_digit_count(a);
    const size_t b_digits = tuple_digit_count(b);

    if (a_digits < b_digits) {
        return -1;
    }
    if (a_digits > b_digits) {
        return 1;
    }
    if (a->original_index < b->original_index) {
        return -1;
    }
    if (a->original_index > b->original_index) {
        return 1;
    }
    return 0;
}

static void sort_tuples_by_total_digits(Tuple *tuples, size_t count)
{
    if (tuples != NULL && count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }
}

static void free_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].values);
    }
    free(tuples);
}

int main(void)
{
    size_t tuple_count;

    if (scanf("%zu", &tuple_count) != 1) {
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = calloc(tuple_count, sizeof(*tuples));
    if (tuple_count != 0 && tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t value_count;

        if (scanf("%zu", &value_count) != 1 ||
            value_count > SIZE_MAX / sizeof(*tuples[i].values)) {
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        tuples[i].values = malloc(value_count * sizeof(*tuples[i].values));
        tuples[i].count = value_count;
        tuples[i].original_index = i;

        if (value_count != 0 && tuples[i].values == NULL) {
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < value_count; ++j) {
            if (scanf("%d", &tuples[i].values[j]) != 1) {
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }
    }

    sort_tuples_by_total_digits(tuples, tuple_count);

    for (size_t i = 0; i < tuple_count; ++i) {
        putchar('(');
        for (size_t j = 0; j < tuples[i].count; ++j) {
            if (j != 0) {
                printf(", ");
            }
            printf("%d", tuples[i].values[j]);
        }
        puts(")");
    }

    free_tuples(tuples, tuple_count);
    return EXIT_SUCCESS;
}