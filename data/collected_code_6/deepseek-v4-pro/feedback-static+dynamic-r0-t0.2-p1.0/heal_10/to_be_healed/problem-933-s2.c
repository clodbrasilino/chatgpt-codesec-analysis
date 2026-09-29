#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdint.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "([a-z0-9])([A-Z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    if (input_len >= SIZE_MAX / 2) {
        regfree(&regex);
        return NULL;
    }

    size_t max_result_len = input_len * 2 + 1;
    char *result = malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;

    while (src_pos < input_len && dst_pos < max_result_len && 
           regexec(&regex, remaining, 2, matches, 0) == 0) {
        size_t match_start = (size_t)matches[0].rm_so;
        size_t match_end = (size_t)matches[0].rm_eo;
        
        size_t copy_len = match_start + 1;
        
        if (copy_len > max_result_len - dst_pos) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        if (dst_pos + copy_len <= max_result_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, remaining, copy_len);
            dst_pos += copy_len;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        if (dst_pos + 2 > max_result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        result[dst_pos++] = '_';
        result[dst_pos++] = (char)tolower((unsigned char)remaining[match_start + 1]);
        
        src_pos += match_end;
        remaining += match_end;
    }

    if (src_pos < input_len) {
        size_t remaining_len = input_len - src_pos;
        
        if (remaining_len > max_result_len - dst_pos) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        if (dst_pos + remaining_len <= max_result_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, remaining, remaining_len);
            dst_pos += remaining_len;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (dst_pos >= max_result_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    
    result[dst_pos] = '\0';
    regfree(&regex);

    for (size_t i = 0; result[i] != '\0'; i++) {
        result[i] = (char)tolower((unsigned char)result[i]);
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "snakeCaseTest",
        "already_snake",
        "UPPERCASE",
        "mixedCASEString",
        "with123Numbers",
        "a",
        "",
        "GoogleAssistant",
        "ChromeCast",
        "QuadCore",
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