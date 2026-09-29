#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool bounded_string_length(const char *string,
                                  size_t maximum_length,
                                  size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return false;
    }

    terminator = memchr(string, '\0', maximum_length);
    if (terminator == NULL) {
        return false;
    }

    *length = (size_t)(terminator - string);
    return true;
}

static bool are_anagrams(const char *first,
                         const char *second,
                         size_t maximum_length)
{
    size_t first_length;
    size_t second_length;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    size_t counts[UCHAR_MAX + 1] = {0};

    if (!bounded_string_length(first, maximum_length, &first_length) ||
        !bounded_string_length(second, maximum_length, &second_length)) {
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
                                  size_t maximum_length,
                                  size_t *match_count)
{
    const char **matches;
    size_t count = 0;
    size_t target_length;

    if (match_count == NULL) {
        return NULL;
    }

    *match_count = 0;

    if (target == NULL ||
        maximum_length == 0 ||
        (strings == NULL && string_count != 0) ||
        !bounded_string_length(target, maximum_length, &target_length)) {
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
        if (strings[i] != NULL &&
            are_anagrams(target, strings[i], maximum_length)) {
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
    const size_t maximum_length = 1024;
    size_t match_count = 0;
    const char **matches = find_anagrams(
        target,
        strings,
        sizeof(strings) / sizeof(strings[0]),
        maximum_length,
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