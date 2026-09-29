#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int *values;
    size_t length;
    size_t original_index;
} Tuple;

static size_t digit_count(int value)
{
    long long number = value;
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

    for (size_t i = 0; i < tuple->length; ++i) {
        total += digit_count(tuple->values[i]);
    }

    return total;
}

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    size_t a_digits = tuple_digit_count(a);
    size_t b_digits = tuple_digit_count(b);

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
        fprintf(stderr, "Failed to read tuple count.\n");
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        fprintf(stderr, "Tuple count is too large.\n");
        return EXIT_FAILURE;
    }

    Tuple *tuples = calloc(tuple_count, sizeof(*tuples));
    if (tuple_count != 0 && tuples == NULL) {
        fprintf(stderr, "Allocation failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t length;

        if (scanf("%zu", &length) != 1) {
            fprintf(stderr, "Failed to read tuple length.\n");
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        if (length > SIZE_MAX / sizeof(*tuples[i].values)) {
            fprintf(stderr, "Tuple length is too large.\n");
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        tuples[i].length = length;
        tuples[i].original_index = i;
        tuples[i].values = malloc(length * sizeof(*tuples[i].values));

        if (length != 0 && tuples[i].values == NULL) {
            fprintf(stderr, "Allocation failed: %s\n", strerror(errno));
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < length; ++j) {
            if (scanf("%d", &tuples[i].values[j]) != 1) {
                fprintf(stderr, "Failed to read tuple value.\n");
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }
    }

    sort_tuples_by_total_digits(tuples, tuple_count);

    for (size_t i = 0; i < tuple_count; ++i) {
        putchar('(');

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (j != 0) {
                printf(", ");
            }
            printf("%d", tuples[i].values[j]);
        }

        printf(")\n");
    }

    free_tuples(tuples, tuple_count);
    return EXIT_SUCCESS;
}