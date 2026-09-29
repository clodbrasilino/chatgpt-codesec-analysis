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
        ch = getchar();
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

    buffer[0] = '\0';

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= capacity) {
            buffer[0] = '\0';
            return discard_token_tail(ch) == 0 ? -1 : -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_uintmax_token(uintmax_t upper_bound, uintmax_t *value)
{
    char buffer[sizeof(uintmax_t) * CHAR_BIT + 2U];
    char *end = NULL;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1 || buffer[0] == '\0' ||
        buffer[0] == '-' || buffer[0] == '+') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > upper_bound) {
        return -1;
    }

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
    if (element_size != 0 && count > SIZE_MAX / element_size) {
        return NULL;
    }

    if (count == 0) {
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
    size_t count = 0;
    uint64_t *values = NULL;
    uint64_t *subset = NULL;
    size_t subset_count = 0;
    int result = EXIT_FAILURE;

    if (read_size(&count) != 0) {
        goto cleanup;
    }

    if (count > 0) {
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
        if (i != 0 && putchar(' ') == EOF) {
            goto cleanup;
        }

        if (fprintf(stdout, "%" PRIu64, subset[i]) < 0) {
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(values);
    free(subset);
    return result;
}