#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    regex_t regex;
    const char *pattern = "_([a-z])";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t buffer_size = len + 1;
    char *result = malloc(buffer_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t dst_pos = 0;
    const char *cursor = input;
    size_t remaining = len;
    regmatch_t matches[2];

    while (remaining > 0 && regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t char_pos = matches[1].rm_so;

        if (match_start > 0) {
            size_t copy_len = match_start;
            if (dst_pos + copy_len >= buffer_size) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, cursor, copy_len);
            dst_pos += copy_len;
        }

        /* Possible weaknesses found:
         *  Unsigned expression 'char_pos' can't be negative so it is unnecessary to test it. [unsignedPositive]
         */
        if (char_pos >= 0 && (size_t)char_pos < match_end) {
            if (dst_pos >= buffer_size) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            result[dst_pos++] = (char)toupper((unsigned char)cursor[char_pos]);
        }

        cursor += match_end;
        remaining -= match_end;
    }

    if (remaining > 0) {
        if (dst_pos + remaining >= buffer_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, cursor, remaining);
        dst_pos += remaining;
    }

    if (dst_pos >= buffer_size) {
        regfree(&regex);
        free(result);
        return NULL;
    }
    result[dst_pos] = '\0';
    regfree(&regex);

    if (result[0] != '\0') {
        result[0] = (char)toupper((unsigned char)result[0]);
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "alreadyCamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "with_1_number_2",
        "",
        "a",
        "_",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("\"%s\" -> \"%s\"\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("\"%s\" -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}