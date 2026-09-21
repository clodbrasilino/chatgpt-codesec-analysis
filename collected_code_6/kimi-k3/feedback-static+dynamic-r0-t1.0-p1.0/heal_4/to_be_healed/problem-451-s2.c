#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* remove_whitespace(const char* input, size_t input_len) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    char* result = NULL;
    size_t result_idx = 0;

    ret = regcomp(&regex, "[[:space:]]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    if (input_len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    const char* cursor = input;
    size_t offset = 0;

    while (offset < input_len) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - offset;
            if (remaining > input_len - result_idx) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, cursor, remaining);
            result_idx += remaining;
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = (size_t)match.rm_so;
        if (match_start > input_len - result_idx) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match_start > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, cursor, match_start);
            result_idx += match_start;
        }
        cursor += match.rm_eo;
        offset += match.rm_eo;
    }

    result[result_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char test_string[] = "Hello World \t This is a test \n string";
    size_t test_len = sizeof(test_string) - 1;
    char* cleaned = remove_whitespace(test_string, test_len);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}