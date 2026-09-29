#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *swap_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    regmatch_t match;
    size_t src_idx = 0;
    size_t dst_idx = 0;

    while (src_idx < len) {
        if (regexec(&regex, input + src_idx, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = match.rm_so;
                if (dst_idx + copy_len > len) {
                    copy_len = len - dst_idx;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_idx, input + src_idx, copy_len);
                dst_idx += copy_len;
            }

            char original_char = input[src_idx + match.rm_so];
            if (original_char == ' ') {
                result[dst_idx++] = '_';
            } else {
                result[dst_idx++] = ' ';
            }

            src_idx += match.rm_eo;
        } else {
            size_t remaining = len - src_idx;
            size_t copy_len = remaining;
            if (dst_idx + copy_len > len) {
                copy_len = len - dst_idx;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_idx, input + src_idx, copy_len);
            dst_idx += copy_len;
            src_idx += remaining;
        }
    }

    result[dst_idx] = '\0';
    regfree(&regex);

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *processed = swap_whitespace_underscore(argv[1]);
    if (processed == NULL) {
        fprintf(stderr, "Memory allocation or regex error\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", processed);
    free(processed);

    return EXIT_SUCCESS;
}