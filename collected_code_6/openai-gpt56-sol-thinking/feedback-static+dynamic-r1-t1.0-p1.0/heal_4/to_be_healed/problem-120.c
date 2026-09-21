#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TOKEN_CAPACITY 64

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static bool read_token(char token[TOKEN_CAPACITY])
{
    char terminator;
    int result;

    if (token == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    result = fscanf(stdin, " %63s", token);
    if (result != 1) {
        return false;
    }

    result = fscanf(stdin, "%c", &terminator);
    if (result == 1) {
        return isspace((unsigned char)terminator) != 0;
    }

    return !ferror(stdin);
}

static bool read_count(size_t *count)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[TOKEN_CAPACITY];
    char *end;
    uintmax_t parsed;

    if (count == NULL || !read_token(token) || token[0] == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return false;
    }

    *count = (size_t)parsed;
    return true;
}

static bool read_int32(int32_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[TOKEN_CAPACITY];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token)) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT32_MIN || parsed > INT32_MAX) {
        return false;
    }

    *value = (int32_t)parsed;
    return true;
}

static bool find_maximum_product(const Tuple *tuples, size_t count,
                                 int64_t *maximum)
{
    int64_t current_maximum;

    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    current_maximum =
        (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > current_maximum) {
            current_maximum = product;
        }
    }

    *maximum = current_maximum;
    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (!read_count(&count) || count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32(&tuples[i].first) ||
            !read_int32(&tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_product(tuples, count, &maximum)) {
        fputs("Unable to find maximum product\n", stderr);
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