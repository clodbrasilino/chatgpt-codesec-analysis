#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    if (strlen(input) >= SIZE_MAX / 2) {
        return NULL;
    }

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

    size_t max_result_len = input_len * 2 + 1;
    char *result = malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;

    while (src_pos < input_len) {
        regmatch_t matches[3];
        int match_result = regexec(&regex, remaining, 3, matches, 0);
        
        if (match_result != 0) {
            break;
        }

        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t group1_start = matches[1].rm_so;
        size_t group1_end = matches[1].rm_eo;
        size_t group2_start = matches[2].rm_so;
        size_t group2_end = matches[2].rm_eo;

        if (match_start > 0) {
            if (dst_pos + match_start >= max_result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dst_pos, remaining, match_start);
            dst_pos += match_start;
        }

        if (group1_end > group1_start && group1_start != (size_t)-1) {
            size_t group1_len = group1_end - group1_start;
            if (dst_pos + group1_len >= max_result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dst_pos, remaining + group1_start, group1_len);
            dst_pos += group1_len;
        }

        if (dst_pos >= max_result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[dst_pos++] = '_';

        if (group2_end > group2_start && group2_start != (size_t)-1) {
            char c = remaining[group2_start];
            if (c >= 'A' && c <= 'Z') {
                c = (char)(c + ('a' - 'A'));
            }
            if (dst_pos >= max_result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result[dst_pos++] = c;
            
            if (group2_end - group2_start > 1) {
                size_t remaining_len = group2_end - group2_start - 1;
                if (dst_pos + remaining_len >= max_result_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(result + dst_pos, remaining + group2_start + 1, remaining_len);
                dst_pos += remaining_len;
            }
        }

        src_pos += match_end;
        remaining += match_end;
    }

    if (src_pos < input_len) {
        size_t remaining_len = input_len - src_pos;
        if (dst_pos + remaining_len >= max_result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + dst_pos, remaining, remaining_len);
        dst_pos += remaining_len;
    }

    if (dst_pos >= max_result_len) {
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