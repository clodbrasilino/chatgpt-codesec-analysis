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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
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

        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;

        if (match_start > 0) {
            if (!append_string(&result, &dst_pos, &dst_capacity, remaining, match_start)) {
                free(result);
                regfree(&regex);
                return NULL;
            }
        }

        if (matches[1].rm_so != -1 && matches[1].rm_eo > matches[1].rm_so) {
            if (!append_char(&result, &dst_pos, &dst_capacity, remaining[matches[1].rm_so])) {
                free(result);
                regfree(&regex);
                return NULL;
            }
        }

        if (!append_char(&result, &dst_pos, &dst_capacity, '_')) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (matches[1].rm_so != -1 && matches[1].rm_eo > matches[1].rm_so) {
            if (matches[1].rm_eo - matches[1].rm_so > 1) {
                if (!append_string(&result, &dst_pos, &dst_capacity, 
                                   remaining + matches[1].rm_so + 1, 
                                   matches[1].rm_eo - matches[1].rm_so - 1)) {
                    free(result);
                    regfree(&regex);
                    return NULL;
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