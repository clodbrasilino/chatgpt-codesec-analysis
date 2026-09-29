#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len >= SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    regmatch_t match;
    const char *cursor = input;
    size_t input_remaining = input_len;

    while (input_remaining > 0 && regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > input_remaining) {
            break;
        }

        if (match_end > input_remaining) {
            match_end = input_remaining;
        }

        if (match_start > 0) {
            if (result_index + match_start > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_index, cursor, match_start);
            result_index += match_start;
        }

        cursor += match_end;
        input_remaining -= match_end;

        if (match_start == match_end) {
            if (input_remaining > 0) {
                cursor++;
                input_remaining--;
            }
        }
    }

    if (input_remaining > 0) {
        if (result_index + input_remaining > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_index, cursor, input_remaining);
        result_index += input_remaining;
    }

    if (result_index > input_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[result_index] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123 - test@example.com";
    char *cleaned = remove_non_alphanumeric(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}