#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char *search_start = input;
    const char *input_end = input + input_len;

    while (1) {
        regmatch_t match;
        ret = regexec(&regex, search_start, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = input_end - search_start;
            if (remaining_len > 0) {
                if (result_idx + remaining_len <= input_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_idx, search_start, remaining_len);
                    result_idx += remaining_len;
                }
            }
            break;
        }

        if (ret != 0) {
            break;
        }

        size_t match_offset = match.rm_so;
        if (match_offset > 0) {
            if (result_idx + match_offset <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, search_start, match_offset);
                result_idx += match_offset;
            }
        }

        search_start += match.rm_eo;
    }

    result[result_idx] = '\0';

    char *trimmed_result = realloc(result, result_idx + 1);
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    regfree(&regex);

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *cleaned = remove_non_alnum(argv[1]);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return 1;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    return 0;
}