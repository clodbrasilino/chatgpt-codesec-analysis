#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int build_frequency(const char *string, size_t *frequency,
                           size_t frequency_count)
{
    const unsigned char *current;

    if (string == NULL || frequency == NULL ||
        frequency_count < (size_t)UCHAR_MAX + 1U) {
        return 0;
    }

    memset(frequency, 0, frequency_count * sizeof(*frequency));

    current = (const unsigned char *)string;
    while (*current != '\0') {
        if (frequency[*current] == SIZE_MAX) {
            return 0;
        }

        ++frequency[*current];
        ++current;
    }

    return 1;
}

static int is_anagram(const char *string, const size_t *target_frequency,
                      size_t frequency_count)
{
    size_t *frequency;
    int result;

    if (string == NULL || target_frequency == NULL ||
        frequency_count < (size_t)UCHAR_MAX + 1U ||
        frequency_count > SIZE_MAX / sizeof(*frequency)) {
        return 0;
    }

    frequency = calloc(frequency_count, sizeof(*frequency));
    if (frequency == NULL) {
        return 0;
    }

    result = build_frequency(string, frequency, frequency_count) &&
             memcmp(frequency, target_frequency,
                    frequency_count * sizeof(*frequency)) == 0;

    free(frequency);
    return result;
}

static size_t find_anagrams(const char *target,
                            const char *const *strings,
                            size_t string_count,
                            const char **results,
                            size_t result_capacity)
{
    const size_t frequency_count = (size_t)UCHAR_MAX + 1U;
    size_t *target_frequency;
    size_t result_count;
    size_t index;

    if (target == NULL ||
        (string_count != 0U && strings == NULL) ||
        (result_capacity != 0U && results == NULL) ||
        frequency_count > SIZE_MAX / sizeof(*target_frequency)) {
        return 0;
    }

    target_frequency = calloc(frequency_count, sizeof(*target_frequency));
    if (target_frequency == NULL) {
        return 0;
    }

    if (!build_frequency(target, target_frequency, frequency_count)) {
        free(target_frequency);
        return 0;
    }

    result_count = 0;

    for (index = 0; index < string_count; ++index) {
        if (strings[index] != NULL &&
            is_anagram(strings[index], target_frequency, frequency_count)) {
            if (result_count < result_capacity) {
                results[result_count] = strings[index];
            }

            if (result_count == SIZE_MAX) {
                free(target_frequency);
                return SIZE_MAX;
            }

            ++result_count;
        }
    }

    free(target_frequency);
    return result_count;
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
        "tinsel",
        "listen"
    };
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    const char **results;
    size_t match_count;
    size_t index;

    if (string_count > SIZE_MAX / sizeof(*results)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    results = malloc(string_count * sizeof(*results));
    if (results == NULL && string_count != 0U) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    match_count = find_anagrams(target, strings, string_count,
                                results, string_count);

    if (match_count > string_count) {
        free(results);
        fputs("Anagram search failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Anagrams of \"%s\":\n", target) < 0) {
        free(results);
        return EXIT_FAILURE;
    }

    for (index = 0; index < match_count; ++index) {
        if (printf("%s\n", results[index]) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);

    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}