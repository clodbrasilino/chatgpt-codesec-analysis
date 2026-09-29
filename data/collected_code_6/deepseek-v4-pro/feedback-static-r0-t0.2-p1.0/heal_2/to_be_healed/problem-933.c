#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    regex_t regex;
    const char *pattern = "([a-z0-9])([A-Z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_result_size = input_len * 2 + 1;
    char *result = malloc(max_result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;
    regmatch_t matches[2];

    while (src_pos < input_len && regexec(&regex, remaining, 2, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t group1_start = matches[1].rm_so;
        size_t group1_end = matches[1].rm_eo;
        size_t group2_start = matches[1].rm_eo;
        size_t group2_end = matches[0].rm_eo;

        if (match_start > 0) {
            size_t copy_size = match_start;
            if (dst_pos + copy_size >= max_result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, remaining, copy_size);
            dst_pos += copy_size;
        }

        if (group1_end > group1_start) {
            size_t copy_size = group1_end - group1_start;
            if (dst_pos + copy_size >= max_result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, remaining + group1_start, copy_size);
            dst_pos += copy_size;
        }

        if (dst_pos >= max_result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[dst_pos++] = '_';

        if (group2_end > group2_start) {
            char lower_char = (char)tolower((unsigned char)remaining[group2_start]);
            if (dst_pos >= max_result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result[dst_pos++] = lower_char;
            
            if (group2_end - group2_start > 1) {
                size_t copy_size = group2_end - group2_start - 1;
                if (dst_pos + copy_size >= max_result_size) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, remaining + group2_start + 1, copy_size);
                dst_pos += copy_size;
            }
        }

        src_pos += match_end;
        remaining = input + src_pos;
    }

    if (src_pos < input_len) {
        size_t copy_size = input_len - src_pos;
        if (dst_pos + copy_size >= max_result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, remaining, copy_size);
        dst_pos += copy_size;
    }

    result[dst_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake",
        "UPPERCASE",
        "mixedCASEString123",
        "a",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}