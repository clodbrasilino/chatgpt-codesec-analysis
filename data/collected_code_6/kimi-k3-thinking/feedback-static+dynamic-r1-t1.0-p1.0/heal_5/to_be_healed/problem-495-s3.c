#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 1048576

static int append_bytes(char *dst, size_t dst_capacity, size_t *dst_len, const char *src, size_t n)
{
    size_t used;
    size_t available;

    if (dst == NULL || dst_len == NULL || (src == NULL && n > 0)) {
        return -1;
    }

    used = *dst_len;
    if (used >= dst_capacity) {
        return -1;
    }

    available = dst_capacity - used - 1;
    if (n > available) {
        return -1;
    }

    if (n > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst + used, src, n);
        *dst_len = used + n;
    }

    return 0;
}

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

    if (input_len >= SIZE_MAX - 1) {
        regfree(&regex);
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
            if (append_bytes(result, capacity, &result_len, cursor, remaining) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
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
        if ((size_t)match.rm_so > remaining || (size_t)match.rm_eo > remaining) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        prefix_len = (size_t)match.rm_so;
        if (append_bytes(result, capacity, &result_len, cursor, prefix_len) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        cursor += match.rm_eo;

        if (match.rm_eo == 0) {
            if (cursor >= end || append_bytes(result, capacity, &result_len, cursor, 1) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            cursor++;
        }
    }

    if (result_len >= capacity) {
        free(result);
        regfree(&regex);
        return NULL;
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