#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *replace_chars_with_colon(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    size_t max_output = input_len * 2 + 1;
    char *result = (char *)malloc(max_output);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_idx = 0;
    size_t dst_idx = 0;
    regmatch_t match;

    while (src_idx < input_len) {
        ret = regexec(&regex, input + src_idx, 1, &match, 0);
        if (ret == 0) {
            size_t match_start = match.rm_so;
            size_t match_end = match.rm_eo;
            
            if (match_start > 0) {
                if (dst_idx + match_start > max_output - 1) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_idx, input + src_idx, match_start);
                dst_idx += match_start;
            }
            
            if (dst_idx + 1 > max_output - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result[dst_idx++] = ':';
            src_idx += match_end;
        } else if (ret == REG_NOMATCH) {
            size_t remaining = input_len - src_idx;
            if (dst_idx + remaining > max_output - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_idx, input + src_idx, remaining);
            dst_idx += remaining;
            break;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[dst_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "Hello, world. This is a test",
        "NoSpecialCharsHere",
        "   ,,,...   ",
        "",
        "Mixed, spaces. and, punctuation.",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *replaced = replace_chars_with_colon(test_strings[i]);
        if (replaced != NULL) {
            printf("Original: \"%s\"\n", test_strings[i]);
            printf("Replaced: \"%s\"\n\n", replaced);
            free(replaced);
        } else {
            printf("Error processing string: \"%s\"\n\n", test_strings[i]);
        }
    }

    return 0;
}