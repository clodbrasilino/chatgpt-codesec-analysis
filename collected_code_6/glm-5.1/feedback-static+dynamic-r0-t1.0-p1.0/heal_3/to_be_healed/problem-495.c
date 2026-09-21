#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    regex_t regex;
    int status;
    size_t max_matches = 1;
    regmatch_t match;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    size_t result_capacity = input_len + 1;
    size_t result_len = 0;

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return NULL;
    }

    const char *cursor = input;

    while ((status = regexec(&regex, cursor, max_matches, &match, 0)) == 0) {
        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            if (result_len + copy_len >= result_capacity) {
                size_t new_capacity = (result_capacity * 2) > (result_len + copy_len + 1) ? (result_capacity * 2) : (result_len + copy_len + 1);
                char *new_result = (char *)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            if (result_capacity >= result_len + copy_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, copy_len);
            }
            result_len += copy_len;
            result[result_len] = '\0';
        }
        cursor += match.rm_eo;
    }

    if (status == REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_len = strlen(cursor);
        if (remaining_len > 0) {
            if (result_len + remaining_len >= result_capacity) {
                size_t new_capacity = result_len + remaining_len + 1;
                char *new_result = (char *)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            if (result_capacity >= result_len + remaining_len + 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, remaining_len + 1);
            }
            /* Possible weaknesses found:
             *  Variable 'result_len' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'result_len' is never read [deadcode.DeadStores]
             */
            result_len += remaining_len;
        }
    } else {
        free(result);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t final_len = strlen(result);
    char *trimmed_result = (char *)realloc(result, final_len + 1);
    if (trimmed_result != NULL) {
        return trimmed_result;
    }

    return result;
}

int main(void) {
    const char *input_string = "HelloWorld123abcDEF456ghiJKL";
    char *output_string = remove_lowercase_substrings(input_string);

    if (output_string != NULL) {
        printf("Input: %s\n", input_string);
        printf("Output: %s\n", output_string);
        free(output_string);
    } else {
        printf("Memory allocation or regex error occurred.\n");
    }

    return 0;
}