#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GoogleDart', got <no output>
  *  test case 0 failed: expected 'GoogleFlutter', got <no output>
  *  test case 2 failed: expected 'iOSSwift', got <no output>
  */

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < input_len && regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            size_t bytes_to_copy = match_start - src_pos;
            if (dst_pos + bytes_to_copy > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, bytes_to_copy);
            dst_pos += bytes_to_copy;
        }

        src_pos = match_end;

        if (match.rm_so == match.rm_eo) {
            if (src_pos < input_len) {
                if (dst_pos >= input_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result[dst_pos++] = input[src_pos++];
            } else {
                break;
            }
        }
    }

    if (src_pos < input_len) {
        size_t remaining = input_len - src_pos;
        if (dst_pos + remaining > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, input + src_pos, remaining);
        dst_pos += remaining;
    }

    if (dst_pos >= input_len + 1) {
        free(result);
        regfree(&regex);
        return NULL;
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
    const char *test_string = "Hello   World\t\n  from C!";
    char *cleaned = remove_whitespaces(test_string);

    if (cleaned == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Original: '%s'\n", test_string);
    printf("Cleaned:  '%s'\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}