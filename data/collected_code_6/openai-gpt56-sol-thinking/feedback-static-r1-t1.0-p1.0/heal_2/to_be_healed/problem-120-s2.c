#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

static bool read_token(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return false;
    }

    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    size_t length = 0;
    bool too_long = false;

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = true;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return !too_long;
}

static bool read_size(size_t *value)
{
    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[sizeof(uintmax_t) * CHAR_BIT + 3];

    if (!read_token(token, sizeof(token)) || token[0] == '-') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int32(int32_t *value)
{
    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[sizeof(uintmax_t) * CHAR_BIT + 3];

    if (!read_token(token, sizeof(token))) {
        return false;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT32_MIN || parsed > INT32_MAX) {
        return false;
    }

    *value = (int32_t)parsed;
    return true;
}

static bool find_maximum_product(const Tuple *tuples, size_t count,
                                 int64_t *result)
{
    if (tuples == NULL || result == NULL || count == 0) {
        return false;
    }

    int64_t maximum =
        (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > maximum) {
            maximum = product;
        }
    }

    *result = maximum;
    return true;
}

int main(void)
{
    size_t count;

    if (!read_size(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32(&tuples[i].first) ||
            !read_int32(&tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t maximum;

    if (!find_maximum_product(tuples, count, &maximum)) {
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