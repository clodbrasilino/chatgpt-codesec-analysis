#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_lowercase_substrings(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[a-z]+";
    size_t input_len;
    char *result;
    size_t result_len = 0;
    const char *cursor;
    int status;

    if (!input) {
        return NULL;
    }

    input_len = strlen(input);
    if (input_len == 0) {
        result = malloc(1);
        if (!result) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    result = malloc(input_len + 1);
    if (!result) {
        return NULL;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status) {
        free(result);
        return NULL;
    }

    cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t prefix_len = (size_t)match.rm_so;
        size_t remaining_len = input_len - (size_t)(cursor - input);

        if (prefix_len > remaining_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (prefix_len > 0) {
            if (result_len + prefix_len > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_len, cursor, prefix_len);
            result_len += prefix_len;
        }

        if (match.rm_eo < 0 || (size_t)match.rm_eo > remaining_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        cursor += (size_t)match.rm_eo;
    }

    {
        size_t cursor_offset = (size_t)(cursor - input);
        size_t remaining;

        if (cursor_offset > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        remaining = input_len - cursor_offset;

        if (result_len + remaining + 1 > input_len + 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (remaining > 0) {
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
        }
        result[result_len] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test1 = "HelloWorld";
    const char *test2 = "abcDEFghiJKL";
    const char *test3 = "NoLowercase";
    const char *test4 = "ALLUPPERCASE";
    const char *test5 = "Mixed123lowercaseUPPER";
    char *cleaned;

    cleaned = remove_lowercase_substrings(test1);
    if (cleaned) {
        printf("Input:    %s\nOutput:   %s\n\n", test1, cleaned);
        free(cleaned);
    }

    cleaned = remove_lowercase_substrings(test2);
    if (cleaned) {
        printf("Input:    %s\nOutput:   %s\n\n", test2, cleaned);
        free(cleaned);
    }

    cleaned = remove_lowercase_substrings(test3);
    if (cleaned) {
        printf("Input:    %s\nOutput:   %s\n\n", test3, cleaned);
        free(cleaned);
    }

    cleaned = remove_lowercase_substrings(test4);
    if (cleaned) {
        printf("Input:    %s\nOutput:   %s\n\n", test4, cleaned);
        free(cleaned);
    }

    cleaned = remove_lowercase_substrings(test5);
    if (cleaned) {
        printf("Input:    %s\nOutput:   %s\n\n", test5, cleaned);
        free(cleaned);
    }

    return 0;
}