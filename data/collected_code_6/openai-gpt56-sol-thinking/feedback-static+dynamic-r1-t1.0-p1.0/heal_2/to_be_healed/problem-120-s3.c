#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool read_token(char *buffer, size_t capacity)
{
    int character;
    size_t length = 0;
    bool too_long = false;

    if (buffer == NULL || capacity < 2) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)character;
        } else {
            too_long = true;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != EOF && !isspace((unsigned char)character));

    buffer[length] = '\0';

    if (character == EOF && ferror(stdin)) {
        return false;
    }

    return !too_long;
}

static bool read_size_value(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) || token[0] == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64_value(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static bool multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return false;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && b < INT64_MAX / a)) {
            return false;
        }
    }

    *result = a * b;
    return true;
}

static bool find_maximum_tuple_product(const Tuple *tuples, size_t count,
                                       int64_t *maximum_product)
{
    int64_t maximum = INT64_MIN;

    if (tuples == NULL || maximum_product == NULL || count == 0) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t product;

        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return false;
        }

        if (product > maximum) {
            maximum = product;
        }
    }

    *maximum_product = maximum;
    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum_product;

    if (!read_size_value(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&tuples[i].first) ||
            !read_int64_value(&tuples[i].second)) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_tuple_product(tuples, count, &maximum_product)) {
        fprintf(stderr, "Unable to calculate maximum product\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", maximum_product);

    free(tuples);
    return EXIT_SUCCESS;
}