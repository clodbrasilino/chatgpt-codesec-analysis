#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096U

static bool bounded_length(const char *string, size_t limit, size_t *length)
{
    const char *end;

    if (string == NULL || length == NULL) {
        return false;
    }

    end = memchr(string, '\0', limit);
    if (end == NULL) {
        return false;
    }

    *length = (size_t)(end - string);
    return true;
}

static bool are_anagrams(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t counts[256] = {0};

    if (!bounded_length(first, MAX_STRING_LENGTH, &first_length) ||
        !bounded_length(second, MAX_STRING_LENGTH, &second_length)) {
        return false;
    }

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
    size_t target_length;

    if (match_count == NULL) {
        return NULL;
    }

    *match_count = 0;

    if (!bounded_length(target, MAX_STRING_LENGTH, &target_length) ||
        (strings == NULL && string_count != 0) ||
        string_count == 0 ||
        string_count > SIZE_MAX / sizeof(*matches)) {
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
        puts("No anagrams found.");
        return EXIT_SUCCESS;
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