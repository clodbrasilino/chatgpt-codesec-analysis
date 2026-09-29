#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, 8192);
    if (input_len >= 8192) {
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
    size_t remaining = input_len;

    while (remaining > 0 && regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            if (result_index + match_start > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, match_start);
            result_index += match_start;
        }

        if (match_end == 0) {
            cursor++;
            remaining--;
            continue;
        }

        cursor += match_end;
        remaining -= match_end;
    }

    if (remaining > 0) {
        if (result_index + remaining > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_index, cursor, remaining);
        result_index += remaining;
    }

    result[result_index] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123";
    char *cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}