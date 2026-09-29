#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[a-z]+";
    char *result;
    size_t input_len;
    size_t result_len;
    size_t result_capacity;
    size_t offset;
    size_t last_end;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 4096);
    if (input_len == 0 || input_len >= 4096) {
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result_capacity = input_len + 1;
    result = (char *)malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    result_len = 0;
    offset = 0;
    last_end = 0;

    while (offset < input_len && regexec(&regex, input + offset, 1, &match, 0) == 0) {
        size_t match_start = offset + match.rm_so;
        size_t match_end = offset + match.rm_eo;

        if (match_start > last_end) {
            size_t copy_len = match_start - last_end;
            if (result_len + copy_len >= result_capacity) {
                size_t new_capacity = result_capacity * 2;
                if (new_capacity < result_len + copy_len + 1) {
                    new_capacity = result_len + copy_len + 1;
                }
                char *new_result = (char *)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, input + last_end, copy_len);
            result_len += copy_len;
        }

        last_end = match_end;
        offset = match_end;

        if (match.rm_eo == match.rm_so) {
            offset++;
        }
    }

    if (last_end < input_len) {
        size_t copy_len = input_len - last_end;
        if (result_len + copy_len >= result_capacity) {
            size_t new_capacity = result_capacity * 2;
            if (new_capacity < result_len + copy_len + 1) {
                new_capacity = result_len + copy_len + 1;
            }
            char *new_result = (char *)realloc(result, new_capacity);
            if (new_result == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
            /* Possible weaknesses found:
             *  Value stored to 'result_capacity' is never read [deadcode.DeadStores]
             */
            result_capacity = new_capacity;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, input + last_end, copy_len);
        result_len += copy_len;
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_string = "HelloWorld123abcXYZdef456";
    char *cleaned_string;

    cleaned_string = remove_lowercase_substrings(test_string);
    if (cleaned_string != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned_string);
        free(cleaned_string);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}