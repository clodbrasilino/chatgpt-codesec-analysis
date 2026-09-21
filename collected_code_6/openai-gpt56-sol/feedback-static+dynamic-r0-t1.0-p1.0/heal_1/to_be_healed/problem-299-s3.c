#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

typedef struct {
    int64_t key;
    int64_t value;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

    if (a->key < b->key) {
        return -1;
    }
    if (a->key > b->key) {
        return 1;
    }
    return 0;
}

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return -1;
    }

    *result = a + b;
    return 0;
}

static int maximum_aggregate(Tuple *tuples, size_t count, int64_t *maximum)
{
    if (tuples == NULL || maximum == NULL || count == 0) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    int64_t current_sum = tuples[0].value;
    int64_t maximum_sum = current_sum;

    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].key == tuples[i - 1].key) {
            if (add_checked(current_sum, tuples[i].value, &current_sum) != 0) {
                return -1;
            }
        } else {
            if (current_sum > maximum_sum) {
                maximum_sum = current_sum;
            }
            current_sum = tuples[i].value;
        }
    }

    if (current_sum > maximum_sum) {
        maximum_sum = current_sum;
    }

    *maximum = maximum_sum;
    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].key, &tuples[i].value) != 2) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t maximum = 0;
    if (maximum_aggregate(tuples, count, &maximum) != 0) {
        fputs("Unable to calculate maximum aggregate\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}