#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static int bounded_string_length(const char *string,
                                 size_t maximum_length,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return 0;
    }

    terminator = memchr(string, '\0', maximum_length);

    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - string);
    return 1;
}

static int are_anagrams(const char *first,
                        size_t first_capacity,
                        const char *second,
                        size_t second_capacity)
{
    size_t first_length;
    size_t second_length;
    size_t counts[UCHAR_MAX + 1] = {0};

    if (!bounded_string_length(first, first_capacity, &first_length) ||
        !bounded_string_length(second, second_capacity, &second_length)) {
        return 0;
    }

    if (first_length != second_length) {
        return 0;
    }

    for (size_t i = 0; i < first_length; ++i) {
        unsigned char character = (unsigned char)first[i];

        if (counts[character] == SIZE_MAX) {
            return 0;
        }

        ++counts[character];
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
                            size_t target_capacity,
                            const char *const strings[],
                            const size_t string_capacities[],
                            size_t string_count,
                            const char *results[],
                            size_t result_capacity)
{
    size_t match_count = 0;

    if (target == NULL ||
        (string_count > 0 &&
         (strings == NULL || string_capacities == NULL))) {
        return 0;
    }

    for (size_t i = 0; i < string_count; ++i) {
        if (strings[i] != NULL &&
            are_anagrams(target,
                         target_capacity,
                         strings[i],
                         string_capacities[i])) {
            if (results != NULL && match_count < result_capacity) {
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
    static const char target[] = "listen";
    static const char string_0[] = "enlist";
    static const char string_1[] = "google";
    static const char string_2[] = "silent";
    static const char string_3[] = "inlets";
    static const char string_4[] = "banana";
    static const char string_5[] = "tinsel";

    const char *strings[] = {
        string_0,
        string_1,
        string_2,
        string_3,
        string_4,
        string_5
    };

    const size_t string_capacities[] = {
        sizeof(string_0),
        sizeof(string_1),
        sizeof(string_2),
        sizeof(string_3),
        sizeof(string_4),
        sizeof(string_5)
    };

    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    const char **results;

    if (string_count > SIZE_MAX / sizeof(*results)) {
        fputs("Result allocation size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    results = calloc(string_count, sizeof(*results));

    if (results == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t match_count = find_anagrams(target,
                                       sizeof(target),
                                       strings,
                                       string_capacities,
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