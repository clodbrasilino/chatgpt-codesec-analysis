#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "_([a-z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t max_result_len = len + 1;
    char *result = malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *cursor = input;

    while (src_pos < len && regexec(&regex, cursor, len - src_pos, matches, 2, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t char_pos = matches[1].rm_so;

        if (match_start > 0) {
            if (dst_pos + match_start > max_result_len - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (dst_pos + match_start <= max_result_len) {
                memcpy(result + dst_pos, cursor, match_start);
                dst_pos += match_start;
            }
        }

        if (char_pos < match_end) {
            char c = cursor[char_pos];
            if (c >= 'a' && c <= 'z') {
                if (dst_pos < max_result_len) {
                    result[dst_pos++] = (char)(c - 32);
                }
            } else {
                if (dst_pos < max_result_len) {
                    result[dst_pos++] = c;
                }
            }
        }

        cursor += match_end;
        src_pos += match_end;
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        if (dst_pos + remaining >= max_result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (dst_pos + remaining <= max_result_len) {
            memcpy(result + dst_pos, cursor, remaining);
            dst_pos += remaining;
        }
    }
    
    if (dst_pos < max_result_len) {
        result[dst_pos] = '\0';
    } else {
        result[max_result_len - 1] = '\0';
    }

    regfree(&regex);
    
    if (result[0] >= 'A' && result[0] <= 'Z') {
        result[0] = (char)(result[0] + 32);
    }
    
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
        "android_tv",
        "google_pixel",
        "apple_watch",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> conversion failed\n", test_cases[i]);
        }
    }

    return 0;
}