#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_STRING_LENGTH 4096U

static int bounded_length(const char *string, size_t capacity, size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL || capacity == 0) {
        return 0;
    }

    terminator = memchr(string, '\0', capacity);
    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - string);
    return 1;
}

static int are_anagrams(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t counts[UCHAR_MAX + 1] = {0};

    if (!bounded_length(first, MAX_STRING_LENGTH, &first_length) ||
        !bounded_length(second, MAX_STRING_LENGTH, &second_length)) {
        return 0;
    }

    if (first_length != second_length) {
        return 0;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++counts[(unsigned char)first[i]];
    }

    for (size_t i = 0; i < second_length; ++i) {
        unsigned char character = (unsigned char)second[i];

        if (counts[character] == 0) {
            return 0;
        }

        --counts[character];
    }

    return 1;
}

static size_t find_anagrams(const char *target,
                            const char *const strings[],
                            size_t string_count,
                            const char *results[],
                            size_t result_capacity)
{
    size_t match_count = 0;

    if (target == NULL ||
        (string_count > 0 && strings == NULL) ||
        (result_capacity > 0 && results == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < string_count; ++i) {
        if (strings[i] != NULL && are_anagrams(target, strings[i])) {
            if (match_count < result_capacity) {
                results[match_count] = strings[i];
            }

            if (match_count == SIZE_MAX) {
                return SIZE_MAX;
            }

            ++match_count;
        }
    }

    return match_count;
}

int main(void)
{
    const char *target = "listen";
    const char *strings[] = {
        "enlist",
        "google",
        "silent",
        "inlets",
        "banana",
        "tinsel"
    };
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    const char **results = calloc(string_count, sizeof(*results));

    if (results == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t match_count = find_anagrams(target,
                                       strings,
                                       string_count,
                                       results,
                                       string_count);

    if (match_count > string_count) {
        free(results);
        fputs("Unexpected result count.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < match_count; ++i) {
        if (printf("%s\n", results[i]) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}