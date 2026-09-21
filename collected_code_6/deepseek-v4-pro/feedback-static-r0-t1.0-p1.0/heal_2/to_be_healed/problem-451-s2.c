#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len == 0) {
        char *empty = (char *)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < input_len) {
        if (regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                if (dst_pos + copy_len > input_len) {
                    copy_len = input_len - dst_pos;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, input + src_pos, copy_len);
                dst_pos += copy_len;
            }
            src_pos += (size_t)match.rm_eo;
            if (src_pos > input_len) {
                src_pos = input_len;
            }
        } else {
            size_t remaining = input_len - src_pos;
            if (dst_pos + remaining > input_len) {
                remaining = input_len - dst_pos;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
            break;
        }
    }

    result[dst_pos] = '\0';
    regfree(&regex);

    char *final_result = (char *)realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "Hello   World\tfrom\nC programming";
    char *cleaned = remove_whitespaces(test_string);
    
    if (cleaned != NULL) {
        printf("Original: '%s'\n", test_string);
        printf("Cleaned:  '%s'\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}