#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
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

static int read_token(char **token)
{
    char *buffer = NULL;
    size_t capacity = 32;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int parse_uintmax_token(uintmax_t upper_bound, uintmax_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(&buffer);
    if (status != 1 || buffer == NULL || buffer[0] == '\0' ||
        buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > upper_bound) {
        free(buffer);
        return -1;
    }

    free(buffer);
    *value = parsed;
    return 0;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax_token((uintmax_t)SIZE_MAX, &parsed) != 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax_token((uintmax_t)UINT64_MAX, &parsed) != 0) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

static void *allocate_array(size_t count, size_t element_size)
{
    if (count == 0 || element_size == 0 ||
        count > SIZE_MAX / element_size) {
        return NULL;
    }

    return malloc(count * element_size);
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
    int status = -1;

    if (subset == NULL || subset_count == NULL ||
        (values == NULL && count != 0)) {
        return -1;
    }

    *subset = NULL;
    *subset_count = 0;

    if (count == 0) {
        return 0;
    }

    sorted = allocate_array(count, sizeof(*sorted));
    lengths = allocate_array(count, sizeof(*lengths));
    previous = allocate_array(count, sizeof(*previous));

    if (sorted == NULL || lengths == NULL || previous == NULL) {
        goto cleanup;
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
                lengths[j] < SIZE_MAX &&
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

    result = allocate_array(best_length, sizeof(*result));
    if (result == NULL) {
        goto cleanup;
    }

    {
        size_t index = best_index;

        for (size_t position = best_length; position > 0; --position) {
            if (index >= count) {
                goto cleanup;
            }

            result[position - 1] = sorted[index];

            if (position > 1) {
                if (previous[index] == SIZE_MAX ||
                    previous[index] >= index) {
                    goto cleanup;
                }

                index = previous[index];
            }
        }
    }

    *subset = result;
    *subset_count = best_length;
    result = NULL;
    status = 0;

cleanup:
    free(result);
    free(sorted);
    free(lengths);
    free(previous);
    return status;
}

int main(void)
{
    size_t count;
    uint64_t *values = NULL;
    uint64_t *subset = NULL;
    size_t subset_count = 0;
    int result = EXIT_FAILURE;

    if (read_size(&count) != 0) {
        goto cleanup;
    }

    if (count != 0) {
        values = allocate_array(count, sizeof(*values));
        if (values == NULL) {
            goto cleanup;
        }

        for (size_t i = 0; i < count; ++i) {
            if (read_uint64(&values[i]) != 0) {
                goto cleanup;
            }
        }
    }

    if (largest_divisible_subset(values, count,
                                 &subset, &subset_count) != 0) {
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