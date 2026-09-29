#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <limits.h>

static int is_valid_input(const char *input) {
    if (input == NULL) {
        return 0;
    }
    size_t len = 0;
    const char *ptr = input;
    while (*ptr != '\0') {
        len++;
        if (len >= SIZE_MAX / 2) {
            return 0;
        }
        ptr++;
    }
    return 1;
}

static char *snake_to_camel(const char *input) {
    if (!is_valid_input(input)) {
        return NULL;
    }

    size_t len = 0;
    const char *ptr = input;
    while (*ptr != '\0' && len < SIZE_MAX) {
        len++;
        ptr++;
    }
    if (len == SIZE_MAX) {
        return NULL;
    }

    if (len == 0) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    regex_t regex;
    const char *pattern = "_([a-z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t result_capacity = len + 1;
    char *result = (char *)malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t dst_pos = 0;
    const char *cursor = input;
    size_t remaining_len = len;
    regmatch_t matches[2];

    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t match_start = (size_t)matches[0].rm_so;
        size_t match_end = (size_t)matches[0].rm_eo;
        size_t letter_pos = (size_t)matches[1].rm_so;

        if (match_start >= remaining_len || match_end > remaining_len || match_end <= match_start) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (letter_pos >= match_end || letter_pos < match_start) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = match_start;
        if (prefix_len > 0) {
            /* Possible weaknesses found:
             *  Assuming that condition 'dst_pos+prefix_len>=result_capacity' is not redundant
             */
            if (dst_pos + prefix_len >= result_capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition 'dst_pos+prefix_len>result_capacity' is always false [knownConditionTrueFalse]
             *  Condition 'dst_pos+prefix_len>result_capacity' is always false
             */
            if (dst_pos + prefix_len > result_capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, cursor, prefix_len);
            dst_pos += prefix_len;
        }

        if (dst_pos >= result_capacity - 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        char upper = (char)toupper((unsigned char)cursor[letter_pos]);
        result[dst_pos++] = upper;

        cursor += match_end;
        remaining_len -= match_end;
    }

    if (*cursor != '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);
        if (remaining > remaining_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Assuming that condition 'dst_pos+remaining>=result_capacity' is not redundant
         */
        if (dst_pos + remaining >= result_capacity) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'dst_pos+remaining>result_capacity' is always false [knownConditionTrueFalse]
         *  Condition 'dst_pos+remaining>result_capacity' is always false
         */
        if (dst_pos + remaining > result_capacity) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, cursor, remaining);
        dst_pos += remaining;
    }
    
    if (dst_pos >= result_capacity) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    
    result[dst_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "alreadycamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "with_1_number",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}