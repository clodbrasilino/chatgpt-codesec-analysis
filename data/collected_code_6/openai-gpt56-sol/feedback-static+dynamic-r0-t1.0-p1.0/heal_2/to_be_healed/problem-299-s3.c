#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    do {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return -1;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 0;
}

static int read_size_value(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0 ||
        buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64_value(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (read_size_value(&count) != 0 || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64_value(&tuples[i].key) != 0 ||
            read_int64_value(&tuples[i].value) != 0) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

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