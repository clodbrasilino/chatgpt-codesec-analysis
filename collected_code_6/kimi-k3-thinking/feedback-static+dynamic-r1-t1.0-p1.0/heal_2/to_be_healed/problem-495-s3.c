#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 1048576

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char *end;
    char *result;
    size_t result_len;
    size_t capacity;
    size_t input_len;
    int status;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);
    if (input_len >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    capacity = input_len + 1;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    end = input + input_len;
    result_len = 0;

    while (cursor < end) {
        size_t remaining;
        size_t prefix_len;

        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            remaining = (size_t)(end - cursor);
            if (remaining > (capacity - 1) - result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
            break;
        }

        if (status != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        remaining = (size_t)(end - cursor);
        if ((size_t)match.rm_eo > remaining) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        prefix_len = (size_t)match.rm_so;
        if (prefix_len > (capacity - 1) - result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, cursor, prefix_len);
        result_len += prefix_len;
        cursor += match.rm_eo;

        if (match.rm_eo == 0) {
            if (result_len >= capacity - 1 || cursor >= end) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result[result_len] = *cursor;
            result_len++;
            cursor++;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "HELLOworldTHISisATEST123abcXYZ",
        "nolowercaseHERE",
        "onlylower",
        "12345!@#$%",
        ""
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_lowercase_substrings(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Error: failed to process string %zu\n", i);
            return EXIT_FAILURE;
        }
        printf("Original: \"%s\"\n", test_strings[i]);
        printf("Cleaned:  \"%s\"\n\n", cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}