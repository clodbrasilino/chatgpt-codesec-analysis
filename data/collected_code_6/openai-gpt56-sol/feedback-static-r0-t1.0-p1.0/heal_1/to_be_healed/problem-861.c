#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int are_anagrams(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t counts[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_length = strlen(second);

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

    if (target == NULL || (string_count > 0 && strings == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < string_count; ++i) {
        if (strings[i] != NULL && are_anagrams(target, strings[i])) {
            if (results != NULL && match_count < result_capacity) {
                results[match_count] = strings[i];
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