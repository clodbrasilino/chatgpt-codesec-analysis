#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool are_anagrams(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t counts[256] = {0};

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++counts[(unsigned char)first[i]];
    }

    for (size_t i = 0; i < second_length; ++i) {
        unsigned char character = (unsigned char)second[i];

        if (counts[character] == 0) {
            return false;
        }

        --counts[character];
    }

    return true;
}

static const char **find_anagrams(const char *target,
                                   const char *const strings[],
                                   size_t string_count,
                                   size_t *match_count)
{
    const char **matches;
    size_t count = 0;

    if (match_count == NULL) {
        return NULL;
    }

    *match_count = 0;

    if (target == NULL || (strings == NULL && string_count != 0)) {
        return NULL;
    }

    if (string_count == 0) {
        return NULL;
    }

    if (string_count > SIZE_MAX / sizeof(*matches)) {
        return NULL;
    }

    matches = malloc(string_count * sizeof(*matches));
    if (matches == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < string_count; ++i) {
        if (strings[i] != NULL && are_anagrams(target, strings[i])) {
            matches[count++] = strings[i];
        }
    }

    if (count == 0) {
        free(matches);
        return NULL;
    }

    *match_count = count;
    return matches;
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
    size_t match_count = 0;
    const char **matches = find_anagrams(
        target,
        strings,
        sizeof(strings) / sizeof(strings[0]),
        &match_count
    );

    if (matches == NULL) {
        if (match_count == 0) {
            puts("No anagrams found.");
            return EXIT_SUCCESS;
        }

        fputs("Failed to find anagrams.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < match_count; ++i) {
        if (puts(matches[i]) == EOF) {
            free(matches);
            return EXIT_FAILURE;
        }
    }

    free(matches);
    return EXIT_SUCCESS;
}