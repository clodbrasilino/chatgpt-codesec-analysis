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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    size_t max_output_len = input_len + 4;
    char *result = (char *)malloc(max_output_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < input_len) {
        int match_result = regexec(&regex, input + src_pos, 1, &match, 0);
        
        if (match_result == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                if (dst_pos + copy_len >= max_output_len) {
                    size_t new_size = max_output_len * 2 + copy_len;
                    char *temp = (char *)realloc(result, new_size);
                    if (temp == NULL) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    max_output_len = new_size;
                }
                if (dst_pos + copy_len <= max_output_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + dst_pos, input + src_pos, copy_len);
                    dst_pos += copy_len;
                }
            }
            if (dst_pos + 1 >= max_output_len) {
                size_t new_size = max_output_len * 2;
                char *temp = (char *)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                max_output_len = new_size;
            }
            result[dst_pos++] = ' ';
            src_pos += match.rm_eo;
        } else if (match_result == REG_NOMATCH) {
            size_t remaining = input_len - src_pos;
            if (dst_pos + remaining + 1 >= max_output_len) {
                size_t new_size = dst_pos + remaining + 1;
                char *temp = (char *)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                max_output_len = new_size;
            }
            if (dst_pos + remaining <= max_output_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, input + src_pos, remaining);
                dst_pos += remaining;
                src_pos = input_len;
            }
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (dst_pos < max_output_len) {
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