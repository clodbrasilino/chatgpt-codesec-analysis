#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int build_frequency(const char *string, size_t frequency[UCHAR_MAX + 1])
{
    const unsigned char *current;

    if (string == NULL || frequency == NULL) {
        return 0;
    }

    memset(frequency, 0, (UCHAR_MAX + 1) * sizeof(*frequency));

    current = (const unsigned char *)string;
    while (*current != '\0') {
        ++frequency[*current];
        ++current;
    }

    return 1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int is_anagram(const char *string,
                      const size_t target_frequency[UCHAR_MAX + 1])
{
    size_t frequency[UCHAR_MAX + 1];

    if (string == NULL || target_frequency == NULL) {
        return 0;
    }

    if (!build_frequency(string, frequency)) {
        return 0;
    }

    return memcmp(frequency, target_frequency, sizeof(frequency)) == 0;
}

static size_t find_anagrams(const char *target,
                            const char *const strings[],
                            size_t string_count,
                            const char **results,
                            size_t result_capacity)
{
    size_t target_frequency[UCHAR_MAX + 1];
    size_t result_count = 0;
    size_t index;

    if (target == NULL || (string_count > 0 && strings == NULL) ||
        (result_capacity > 0 && results == NULL)) {
        return 0;
    }

    if (!build_frequency(target, target_frequency)) {
        return 0;
    }

    for (index = 0; index < string_count; ++index) {
        if (strings[index] != NULL &&
            is_anagram(strings[index], target_frequency)) {
            if (result_count < result_capacity) {
                results[result_count] = strings[index];
            }
            ++result_count;
        }
    }

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
    if (results == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    match_count = find_anagrams(target, strings, string_count,
                                 results, string_count);

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

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}