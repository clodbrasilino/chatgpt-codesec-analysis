#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int compare_uint64(const void *lhs, const void *rhs)
{
    const uint64_t a = *(const uint64_t *)lhs;
    const uint64_t b = *(const uint64_t *)rhs;

    return (a > b) - (a < b);
}

static int divides(uint64_t a, uint64_t b)
{
    return a == UINT64_C(0) ? b == UINT64_C(0)
                            : b % a == UINT64_C(0);
}

static int discard_token_tail(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1) {
            buffer[0] = '\0';
            /* Possible weaknesses found:
             *  Same value in both branches of ternary operator. [duplicateValueTernary]
             */
            return discard_token_tail(ch) == 0 ? -1 : -1;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(size_t) * CHAR_BIT + 2];
    char *end;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1 || buffer[0] == '\0' || buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(uint64_t) * CHAR_BIT + 2];
    char *end;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1 || buffer[0] == '\0' || buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

static int largest_divisible_subset(const uint64_t *values, size_t count,
                                    uint64_t **subset, size_t *subset_count)
{
    uint64_t *sorted = NULL;
    uint64_t *result = NULL;
    size_t *lengths = NULL;
    size_t *previous = NULL;
    size_t best_index = 0;
    size_t best_length = 0;

    if (subset == NULL || subset_count == NULL ||
        (values == NULL && count != 0)) {
        return -1;
    }

    *subset = NULL;
    *subset_count = 0;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*sorted) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    sorted = malloc(count * sizeof(*sorted));
    lengths = malloc(count * sizeof(*lengths));
    previous = malloc(count * sizeof(*previous));

    if (sorted == NULL || lengths == NULL || previous == NULL) {
        free(sorted);
        free(lengths);
        free(previous);
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_uint64);

    for (size_t i = 0; i < count; ++i) {
        lengths[i] = 1;
        previous[i] = SIZE_MAX;

        for (size_t j = 0; j < i; ++j) {
            if (divides(sorted[j], sorted[i]) &&
                lengths[j] + 1 > lengths[i]) {
                lengths[i] = lengths[j] + 1;
                previous[i] = j;
            }
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    if (best_length > SIZE_MAX / sizeof(*result)) {
        free(sorted);
        free(lengths);
        free(previous);
        return -1;
    }

    result = malloc(best_length * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        free(lengths);
        free(previous);
        return -1;
    }

    {
        size_t index = best_index;

        for (size_t position = best_length; position != 0; --position) {
            result[position - 1] = sorted[index];

            if (position > 1) {
                if (previous[index] == SIZE_MAX) {
                    free(result);
                    free(sorted);
                    free(lengths);
                    free(previous);
                    return -1;
                }

                index = previous[index];
            }
        }
    }

    free(sorted);
    free(lengths);
    free(previous);

    *subset = result;
    *subset_count = best_length;
    return 0;
}

int main(void)
{
    size_t count = 0;
    uint64_t *values = NULL;
    uint64_t *subset = NULL;
    size_t subset_count = 0;
    int result = EXIT_FAILURE;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        goto cleanup;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            goto cleanup;
        }

        for (size_t i = 0; i < count; ++i) {
            if (read_uint64(&values[i]) != 0) {
                goto cleanup;
            }
        }
    }

    if (largest_divisible_subset(values, count, &subset, &subset_count) != 0) {
        goto cleanup;
    }

    for (size_t i = 0; i < subset_count; ++i) {
        if (i != 0 && fputc(' ', stdout) == EOF) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder fprintf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        if (fprintf(stdout, "%" PRIu64, subset[i]) < 0) {
            goto cleanup;
        }
    }

    if (fputc('\n', stdout) == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(values);
    free(subset);
    return result;
}