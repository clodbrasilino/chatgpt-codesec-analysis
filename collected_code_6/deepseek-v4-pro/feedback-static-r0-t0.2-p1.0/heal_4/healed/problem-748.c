#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_before_capitals(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "[A-Z]";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t max_result_len = input_len * 2 + 1;
    char *result = (char *)malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t dst_pos = 0;
    size_t src_pos = 0;

    while (input[src_pos] != '\0') {
        regmatch_t matches[1];
        ret = regexec(&regex, input + src_pos, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = input_len - src_pos;
            if (dst_pos + remaining_len >= max_result_len) {
                remaining_len = max_result_len - dst_pos - 1;
            }
            if (remaining_len > 0 && dst_pos + remaining_len < max_result_len) {
                memcpy(result + dst_pos, input + src_pos, remaining_len);
                dst_pos += remaining_len;
            }
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_pos = matches[0].rm_so;
        if (match_pos > 0) {
            if (dst_pos + match_pos >= max_result_len) {
                match_pos = max_result_len - dst_pos - 1;
            }
            if (match_pos > 0 && dst_pos + match_pos < max_result_len) {
                memcpy(result + dst_pos, input + src_pos, match_pos);
                dst_pos += match_pos;
            }
            if (dst_pos < max_result_len - 1) {
                result[dst_pos++] = ' ';
            }
        }

        if (dst_pos < max_result_len - 1) {
            result[dst_pos++] = input[src_pos + match_pos];
        }
        src_pos += match_pos + 1;
    }

    if (dst_pos < max_result_len) {
        result[dst_pos] = '\0';
    } else {
        result[max_result_len - 1] = '\0';
    }
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "ThisIsATestString",
        "already separated words",
        "ALL CAPS",
        "MixedCaseWithNumbers123AndSymbols!",
        "",
        "single",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *result = add_spaces_before_capitals(test_strings[i]);
        if (result != NULL) {
            printf("Input:    '%s'\n", test_strings[i]);
            printf("Output:   '%s'\n\n", result);
            free(result);
        } else {
            printf("Error processing: '%s'\n\n", test_strings[i]);
        }
    }

    return 0;
}