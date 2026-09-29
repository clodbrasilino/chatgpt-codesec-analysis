#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *escape_regex_literal(const char *literal)
{
    static const char metacharacters[] = ".^$*+?()[]{}|\\";
    size_t length;
    size_t capacity;
    char *escaped;
    char *output;

    if (literal == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(literal);
    if (length > (SIZE_MAX - 1U) / 2U) {
        return NULL;
    }

    capacity = length * 2U + 1U;
    escaped = malloc(capacity);
    if (escaped == NULL) {
        return NULL;
    }

    output = escaped;
    for (const char *input = literal; *input != '\0'; ++input) {
        if (strchr(metacharacters, *input) != NULL) {
            *output++ = '\\';
        }
        *output++ = *input;
    }
    *output = '\0';

    return escaped;
}

static int search_literal_strings(const char *text,
                                  const char *const literals[],
                                  size_t literal_count)
{
    int result = EXIT_SUCCESS;

    if (text == NULL || (literal_count > 0U && literals == NULL)) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < literal_count; ++i) {
        regex_t regex;
        char *pattern;
        int status;

        pattern = escape_regex_literal(literals[i]);
        if (pattern == NULL) {
            fprintf(stderr, "Unable to prepare literal at index %zu\n", i);
            result = EXIT_FAILURE;
            continue;
        }

        status = regcomp(&regex, pattern, REG_EXTENDED);
        free(pattern);

        if (status != 0) {
            size_t error_size = regerror(status, &regex, NULL, 0U);
            char *error_message = malloc(error_size);

            if (error_message != NULL) {
                regerror(status, &regex, error_message, error_size);
                fprintf(stderr, "Regex compilation failed: %s\n", error_message);
                free(error_message);
            } else {
                fputs("Regex compilation failed\n", stderr);
            }

            result = EXIT_FAILURE;
            continue;
        }

        status = regexec(&regex, text, 0U, NULL, 0);
        if (status == 0) {
            printf("\"%s\": found\n", literals[i]);
        } else if (status == REG_NOMATCH) {
            printf("\"%s\": not found\n", literals[i]);
        } else {
            size_t error_size = regerror(status, &regex, NULL, 0U);
            char *error_message = malloc(error_size);

            if (error_message != NULL) {
                regerror(status, &regex, error_message, error_size);
                fprintf(stderr, "Regex search failed: %s\n", error_message);
                free(error_message);
            } else {
                fputs("Regex search failed\n", stderr);
            }

            result = EXIT_FAILURE;
        }

        regfree(&regex);
    }

    return result;
}

int main(void)
{
    const char *text = "C supports regex through POSIX. Literal symbols like a+b are escaped.";
    const char *literals[] = {
        "POSIX",
        "a+b",
        "missing",
        "regex"
    };

    return search_literal_strings(
        text,
        literals,
        sizeof(literals) / sizeof(literals[0])
    );
}