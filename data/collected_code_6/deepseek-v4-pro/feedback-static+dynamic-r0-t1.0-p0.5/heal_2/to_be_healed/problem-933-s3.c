#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got Google_assistant
  *  test case 2 failed: expected 'quad_core', got Quad_core
  *  test case 1 failed: expected 'chrome_cast', got Chrome_cast
  */

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len >= SIZE_MAX / 2) {
        regfree(&regex);
        return NULL;
    }

    char *result = malloc(input_len * 2 + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;

    while (src_pos < input_len && regexec(&regex, remaining, 2, matches, 0) == 0) {
        size_t match_end = matches[0].rm_eo;
        size_t first_end = matches[1].rm_eo;

        if (dst_pos + first_end >= input_len * 2 + 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, remaining, first_end);
        dst_pos += first_end;
        
        if (dst_pos + 2 >= input_len * 2 + 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[dst_pos++] = '_';
        result[dst_pos++] = (char)tolower((unsigned char)remaining[first_end]);

        src_pos += match_end;
        remaining = input + src_pos;
    }

    if (src_pos < input_len) {
        if (dst_pos + (input_len - src_pos) >= input_len * 2 + 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, remaining, input_len - src_pos);
        dst_pos += input_len - src_pos;
    }

    result[dst_pos] = '\0';
    regfree(&regex);

    char *final_result = realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_cases[] = {
        "chromeCast",
        "googleAssistant",
        "quadCore",
        "camelCase",
        "thisIsATest",
        "already_snake",
        "with123Numbers",
        "UPPERCASE",
        "",
        "a",
        "A",
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