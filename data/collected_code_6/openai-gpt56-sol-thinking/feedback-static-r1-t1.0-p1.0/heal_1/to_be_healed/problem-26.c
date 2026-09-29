#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

static bool read_size(FILE *stream, size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    uintmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (stream == NULL || value == NULL || fscanf(stream, "%127s", token) != 1) {
        return false;
    }

    if (token[0] == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int(FILE *stream, int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    intmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (stream == NULL || value == NULL || fscanf(stream, "%127s", token) != 1) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return false;
    }

    *value = (int)parsed;
    return true;
}

static bool tuple_list_has_all_k(const Tuple *tuples, size_t tuple_count, int k)
{
    size_t i;
    size_t j;

    if (tuples == NULL && tuple_count != 0) {
        return false;
    }

    for (i = 0; i < tuple_count; ++i) {
        bool found = false;

        if (tuples[i].elements == NULL && tuples[i].count != 0) {
            return false;
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (tuples[i].elements[j] == k) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

static void free_tuples(Tuple *tuples, size_t tuple_count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < tuple_count; ++i) {
        free(tuples[i].elements);
    }

    free(tuples);
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t tuple_count;
    size_t i;
    size_t j;
    int k;
    bool result;

    if (!read_size(stdin, &tuple_count) || !read_int(stdin, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_count != 0) {
        tuples = calloc(tuple_count, sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < tuple_count; ++i) {
        if (!read_size(stdin, &tuples[i].count)) {
            fputs("Invalid tuple size\n", stderr);
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        if (tuples[i].count > SIZE_MAX / sizeof(*tuples[i].elements)) {
            fputs("Tuple size is too large\n", stderr);
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        if (tuples[i].count != 0) {
            tuples[i].elements = malloc(tuples[i].count *
                                        sizeof(*tuples[i].elements));
            if (tuples[i].elements == NULL) {
                fputs("Memory allocation failed\n", stderr);
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (!read_int(stdin, &tuples[i].elements[j])) {
                fputs("Invalid tuple element\n", stderr);
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }
    }

    result = tuple_list_has_all_k(tuples, tuple_count, k);
    free_tuples(tuples, tuple_count);

    if (puts(result ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}