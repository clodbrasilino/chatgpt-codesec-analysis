#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_chars_with_colon(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "[ ,.]";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    size_t result_size = input_len + 1;
    char *result = (char *)malloc(result_size);
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
                while (dst_idx + match_start >= result_size) {
                    size_t new_size = result_size * 2;
                    if (new_size <= result_size) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    char *temp = (char *)realloc(result, new_size);
                    if (temp == NULL) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    result_size = new_size;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_idx, input + src_idx, match_start);
                dst_idx += match_start;
            }

            while (dst_idx + 1 >= result_size) {
                size_t new_size = result_size * 2;
                if (new_size <= result_size) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                char *temp = (char *)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                result_size = new_size;
            }
            result[dst_idx++] = ':';
            src_idx += match_end;
        } else if (ret == REG_NOMATCH) {
            size_t remaining = input_len - src_idx;
            while (dst_idx + remaining >= result_size) {
                size_t new_size = result_size * 2;
                if (new_size <= result_size) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                char *temp = (char *)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                result_size = new_size;
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

    while (dst_idx >= result_size) {
        size_t new_size = dst_idx + 1;
        char *temp = (char *)realloc(result, new_size);
        if (temp == NULL) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = temp;
        result_size = new_size;
    }
    result[dst_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "Hello, world. This is a test";
    char *modified = replace_chars_with_colon(test_str);
    
    if (modified != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}