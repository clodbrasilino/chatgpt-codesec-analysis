#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *add_spaces_before_capitals(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        if (input_len >= SIZE_MAX - 1) {
            return NULL;
        }
        input_len++;
    }

    if (input_len == 0) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    regex_t regex;
    const char *pattern = "([A-Z])";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return NULL;
    }

    size_t result_len = input_len + 1;
    const char *cursor = input;
    regmatch_t matches[2];

    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
        if (matches[0].rm_so >= 0) {
            if (matches[0].rm_so != 0 || cursor != input) {
                if (result_len < SIZE_MAX) {
                    result_len++;
                } else {
                    regfree(&regex);
                    return NULL;
                }
            }
        }
        if (matches[0].rm_eo == 0) {
            break;
        }
        size_t advance = (size_t)matches[0].rm_eo;
        cursor += advance;
    }

    char *result = (char *)malloc(result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    if (dst_pos < result_len && input[0] >= 'A' && input[0] <= 'Z') {
        result[dst_pos++] = input[src_pos++];
    }

    cursor = input + src_pos;
    while (dst_pos < result_len && regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t match_start = (size_t)matches[0].rm_so;
        size_t match_end = (size_t)matches[0].rm_eo;

        if (match_start > 0) {
            if (dst_pos + match_start > result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dst_pos, cursor, match_start);
            dst_pos += match_start;
        }

        if (dst_pos > 0 && dst_pos < result_len && result[dst_pos - 1] != ' ') {
            result[dst_pos++] = ' ';
        }

        size_t copy_len = match_end - match_start;
        if (!(match_start == 0 && src_pos == 0 && input[0] >= 'A' && input[0] <= 'Z')) {
            if (dst_pos + copy_len > result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dst_pos, cursor + match_start, copy_len);
            dst_pos += copy_len;
        }

        cursor += match_end;
        src_pos += match_end;

        if (match_end == 0) {
            break;
        }
    }

    if (*cursor != '\0') {
        size_t remaining = 0;
        while (cursor[remaining] != '\0') {
            if (remaining >= SIZE_MAX - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            remaining++;
        }
        if (dst_pos + remaining > result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + dst_pos, cursor, remaining);
        dst_pos += remaining;
    }

    if (dst_pos < result_len) {
        result[dst_pos] = '\0';
    } else {
        free(result);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test1 = "HelloWorldExample";
    const char *test2 = "thisIsASampleString";
    const char *test3 = "already separated words";
    const char *test4 = "";
    const char *test5 = "UPPERCASE";
    const char *test6 = "noSpacesHere";

    char *result1 = add_spaces_before_capitals(test1);
    char *result2 = add_spaces_before_capitals(test2);
    char *result3 = add_spaces_before_capitals(test3);
    char *result4 = add_spaces_before_capitals(test4);
    char *result5 = add_spaces_before_capitals(test5);
    char *result6 = add_spaces_before_capitals(test6);

    printf("Input: %s\nOutput: %s\n\n", test1, result1 ? result1 : "NULL");
    printf("Input: %s\nOutput: %s\n\n", test2, result2 ? result2 : "NULL");
    printf("Input: %s\nOutput: %s\n\n", test3, result3 ? result3 : "NULL");
    printf("Input: %s\nOutput: %s\n\n", test4, result4 ? result4 : "NULL");
    printf("Input: %s\nOutput: %s\n\n", test5, result5 ? result5 : "NULL");
    printf("Input: %s\nOutput: %s\n\n", test6, result6 ? result6 : "NULL");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);

    return 0;
}