#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

static int append_char(char **dest, size_t *dst_pos, size_t *dst_capacity, char c) {
    if (*dst_pos + 1 >= *dst_capacity) {
        size_t new_capacity = *dst_capacity * 2;
        char *temp = realloc(*dest, new_capacity);
        if (temp == NULL) {
            return 0;
        }
        *dest = temp;
        *dst_capacity = new_capacity;
    }
    (*dest)[(*dst_pos)++] = c;
    return 1;
}

static int append_string(char **dest, size_t *dst_pos, size_t *dst_capacity, const char *src, size_t len) {
    if (len == 0) {
        return 1;
    }
    /* Possible weaknesses found:
     *  Assuming that condition '*dst_pos+len>=*dst_capacity' is not redundant
     */
    while (*dst_pos + len >= *dst_capacity) {
        size_t new_capacity = *dst_capacity * 2;
        char *temp = realloc(*dest, new_capacity);
        if (temp == NULL) {
            return 0;
        }
        *dest = temp;
        *dst_capacity = new_capacity;
    }
    /* Possible weaknesses found:
     *  Condition '*dst_pos+len>*dst_capacity' is always false
     *  Condition '*dst_pos+len>*dst_capacity' is always false [knownConditionTrueFalse]
     */
    if (*dst_pos + len > *dst_capacity) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(*dest + *dst_pos, src, len);
    *dst_pos += len;
    return 1;
}

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "([a-z0-9])([A-Z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
        if (input_len > SIZE_MAX / 2) {
            regfree(&regex);
            return NULL;
        }
    }

    size_t dst_capacity = input_len * 2 + 1;
    if (dst_capacity < 64) {
        dst_capacity = 64;
    }
    char *result = malloc(dst_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;

    while (src_pos < input_len) {
        regmatch_t matches[2];
        int rc = regexec(&regex, remaining, 2, matches, 0);
        if (rc != 0) {
            break;
        }

        size_t match_start = (size_t)matches[0].rm_so;
        size_t match_end = (size_t)matches[0].rm_eo;

        if (match_start > input_len - src_pos || match_end > input_len - src_pos) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match_start > 0) {
            if (!append_string(&result, &dst_pos, &dst_capacity, remaining, match_start)) {
                free(result);
                regfree(&regex);
                return NULL;
            }
        }

        if (matches[1].rm_so != -1 && matches[1].rm_eo > matches[1].rm_so) {
            if ((size_t)matches[1].rm_so < match_end) {
                if (!append_char(&result, &dst_pos, &dst_capacity, remaining[matches[1].rm_so])) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
            }
        }

        if (!append_char(&result, &dst_pos, &dst_capacity, '_')) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (matches[1].rm_so != -1 && matches[1].rm_eo > matches[1].rm_so) {
            if ((size_t)matches[1].rm_eo - (size_t)matches[1].rm_so > 1) {
                size_t tail_len = (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so - 1;
                if ((size_t)matches[1].rm_so + 1 + tail_len <= input_len - src_pos) {
                    if (!append_string(&result, &dst_pos, &dst_capacity, 
                                       remaining + matches[1].rm_so + 1, 
                                       tail_len)) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                }
            }
        }

        src_pos += match_end;
        remaining += match_end;
    }

    if (src_pos < input_len) {
        if (!append_string(&result, &dst_pos, &dst_capacity, remaining, input_len - src_pos)) {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (dst_pos >= dst_capacity) {
        char *temp = realloc(result, dst_pos + 1);
        if (temp == NULL) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = temp;
    }
    result[dst_pos] = '\0';

    for (size_t i = 0; i < dst_pos; i++) {
        result[i] = (char)tolower((unsigned char)result[i]);
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake",
        "with123Numbers",
        "HTMLElement",
        "",
        "a",
        "ABC",
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