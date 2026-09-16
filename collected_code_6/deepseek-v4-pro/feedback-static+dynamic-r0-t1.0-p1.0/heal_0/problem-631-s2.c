#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "[ _]";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_idx = 0, dst_idx = 0;
    regmatch_t match;

    while (src_idx < len) {
        int match_ret = regexec(&regex, input + src_idx, 1, &match, 0);
        if (match_ret == REG_NOMATCH) {
            size_t remaining = len - src_idx;
            memcpy(result + dst_idx, input + src_idx, remaining);
            dst_idx += remaining;
            break;
        } else if (match_ret == 0) {
            size_t match_start = src_idx + match.rm_so;
            size_t match_end = src_idx + match.rm_eo;

            if (match_start > src_idx) {
                size_t copy_len = match_start - src_idx;
                memcpy(result + dst_idx, input + src_idx, copy_len);
                dst_idx += copy_len;
            }

            if (match.rm_so == match.rm_eo) {
                result[dst_idx++] = input[match_start];
                src_idx = match_end + 1;
                continue;
            }

            char matched_char = input[match_start];
            if (matched_char == ' ') {
                result[dst_idx++] = '_';
            } else if (matched_char == '_') {
                result[dst_idx++] = ' ';
            }
            src_idx = match_end;
        } else {
            regfree(&regex);
            free(result);
            return NULL;
        }
    }

    result[dst_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test1 = "hello world_this_is_a_test";
    const char *test2 = "no_spaces_here";
    const char *test3 = "   ___   ";
    const char *test4 = "";
    const char *test5 = NULL;

    char *res1 = replace_whitespace_underscore(test1);
    char *res2 = replace_whitespace_underscore(test2);
    char *res3 = replace_whitespace_underscore(test3);
    char *res4 = replace_whitespace_underscore(test4);
    char *res5 = replace_whitespace_underscore(test5);

    printf("Test 1: %s -> %s\n", test1, res1 ? res1 : "(null)");
    printf("Test 2: %s -> %s\n", test2, res2 ? res2 : "(null)");
    printf("Test 3: %s -> %s\n", test3, res3 ? res3 : "(null)");
    printf("Test 4: %s -> %s\n", test4, res4 ? res4 : "(null)");
    printf("Test 5: %s -> %s\n", test5 ? test5 : "(null)", res5 ? res5 : "(null)");

    free(res1);
    free(res2);
    free(res3);
    free(res4);
    free(res5);

    return 0;
}