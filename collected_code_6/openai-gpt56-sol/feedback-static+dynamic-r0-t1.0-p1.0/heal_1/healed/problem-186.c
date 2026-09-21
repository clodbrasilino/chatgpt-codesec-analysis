#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *escape_regex_literal(const char *literal, size_t literal_length)
{
    static const char metacharacters[] = ".^$*+?()[]{}|\\";
    size_t extra = 0U;
    size_t capacity;
    char *escaped;
    char *output;

    if (literal == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < literal_length; ++i) {
        if (literal[i] == '\0') {
            return NULL;
        }

        if (strchr(metacharacters, (unsigned char)literal[i]) != NULL) {
            if (extra == SIZE_MAX) {
                return NULL;
            }
            ++extra;
        }
    }

    if (literal_length > SIZE_MAX - extra - 1U) {
        return NULL;
    }

    capacity = literal_length + extra + 1U;
    escaped = malloc(capacity);
    if (escaped == NULL) {
        return NULL;
    }

    output = escaped;
    for (size_t i = 0U; i < literal_length; ++i) {
        if (strchr(metacharacters, (unsigned char)literal[i]) != NULL) {
            *output++ = '\\';
        }
        *output++ = literal[i];
    }
    *output = '\0';

    return escaped;
}

static void report_regex_error(const char *prefix, int status, regex_t *regex)
{
    size_t error_size = regerror(status, regex, NULL, 0U);
    char *error_message;

    if (error_size == 0U) {
        fprintf(stderr, "%s\n", prefix);
        return;
    }

    error_message = malloc(error_size);
    if (error_message == NULL) {
        fprintf(stderr, "%s\n", prefix);
        return;
    }

    regerror(status, regex, error_message, error_size);
    fprintf(stderr, "%s: %s\n", prefix, error_message);
    free(error_message);
}

static int search_literal_strings(const char *text,
                                  const char *const literals[],
                                  const size_t literal_lengths[],
                                  size_t literal_count)
{
    int result = EXIT_SUCCESS;

    if (text == NULL ||
        (literal_count > 0U &&
         (literals == NULL || literal_lengths == NULL))) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < literal_count; ++i) {
        regex_t regex;
        char *pattern;
        int status;

        if (literals[i] == NULL) {
            fprintf(stderr, "Invalid literal at index %zu\n", i);
            result = EXIT_FAILURE;
            continue;
        }

        pattern = escape_regex_literal(literals[i], literal_lengths[i]);
        if (pattern == NULL) {
            fprintf(stderr, "Unable to prepare literal at index %zu\n", i);
            result = EXIT_FAILURE;
            continue;
        }

        status = regcomp(&regex, pattern, REG_EXTENDED);
        free(pattern);

        if (status != 0) {
            report_regex_error("Regex compilation failed", status, &regex);
            result = EXIT_FAILURE;
            continue;
        }

        status = regexec(&regex, text, 0U, NULL, 0);
        if (status == 0) {
            printf("\"%.*s\": found\n",
                   (int)literal_lengths[i], literals[i]);
        } else if (status == REG_NOMATCH) {
            printf("\"%.*s\": not found\n",
                   (int)literal_lengths[i], literals[i]);
        } else {
            report_regex_error("Regex search failed", status, &regex);
            result = EXIT_FAILURE;
        }

        regfree(&regex);
    }

    return result;
}

int main(void)
{
    static const char text[] =
        "C supports regex through POSIX. Literal symbols like a+b are escaped.";
    static const char literal_0[] = "POSIX";
    static const char literal_1[] = "a+b";
    static const char literal_2[] = "missing";
    static const char literal_3[] = "regex";
    static const char *const literals[] = {
        literal_0,
        literal_1,
        literal_2,
        literal_3
    };
    static const size_t literal_lengths[] = {
        sizeof(literal_0) - 1U,
        sizeof(literal_1) - 1U,
        sizeof(literal_2) - 1U,
        sizeof(literal_3) - 1U
    };

    return search_literal_strings(
        text,
        literals,
        literal_lengths,
        sizeof(literals) / sizeof(literals[0])
    );
}