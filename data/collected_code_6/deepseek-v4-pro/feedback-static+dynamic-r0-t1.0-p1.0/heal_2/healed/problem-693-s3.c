#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]{2,}", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t max_result_len = input_len + 1;
    char *result = (char *)malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < input_len && input[src_pos] != '\0') {
        int match_result = regexec(&regex, input + src_pos, 1, &match, 0);
        
        if (match_result == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                if (dst_pos + copy_len >= max_result_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(result + dst_pos, input + src_pos, copy_len);
                dst_pos += copy_len;
            }
            if (dst_pos + 1 >= max_result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result[dst_pos++] = ' ';
            src_pos += match.rm_eo;
        } else if (match_result == REG_NOMATCH) {
            size_t remaining = input_len - src_pos;
            if (dst_pos + remaining >= max_result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
            src_pos = input_len;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
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
    const char *test_strings[] = {
        "Hello   World",
        "  Multiple   spaces   here  ",
        "NoSpaces",
        "",
        "   ",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *cleaned = remove_multiple_spaces(test_strings[i]);
        if (cleaned != NULL) {
            printf("Original: \"%s\"\n", test_strings[i]);
            printf("Cleaned:  \"%s\"\n\n", cleaned);
            free(cleaned);
        } else {
            printf("Error processing string %d\n", i);
        }
    }

    return 0;
}