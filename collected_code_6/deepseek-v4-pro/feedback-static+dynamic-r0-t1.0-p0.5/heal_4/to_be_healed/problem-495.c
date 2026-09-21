#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (reti) {
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

    size_t result_pos = 0;
    size_t search_pos = 0;
    regmatch_t match;

    while (search_pos < input_len && regexec(&regex, input + search_pos, 1, &match, 0) == 0) {
        size_t match_start = search_pos + match.rm_so;
        size_t match_end = search_pos + match.rm_eo;

        if (match_start > search_pos) {
            size_t copy_len = match_start - search_pos;
            if (result_pos + copy_len < result_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_pos, input + search_pos, copy_len);
                result_pos += copy_len;
            } else {
                break;
            }
        }

        search_pos = match_end;

        if (match.rm_so == match.rm_eo) {
            if (search_pos < input_len) {
                if (result_pos + 1 < result_size) {
                    result[result_pos++] = input[search_pos];
                } else {
                    break;
                }
                search_pos++;
            } else {
                break;
            }
        }
    }

    if (search_pos < input_len) {
        size_t remaining_len = input_len - search_pos;
        if (result_pos + remaining_len < result_size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_pos, input + search_pos, remaining_len);
            result_pos += remaining_len;
        } else {
            size_t space_left = result_size - result_pos - 1;
            if (space_left > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_pos, input + search_pos, space_left);
                result_pos += space_left;
            }
        }
    }

    if (result_pos < result_size) {
        result[result_pos] = '\0';
    } else {
        result[result_size - 1] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "abc123def456",
        "UPPERlowerMIXEDcase",
        "NoLowercaseHere",
        "alllowercase",
        "",
        "aBcDeFgHiJkLmNoPqRsTuVwXyZ",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *result = remove_lowercase_substrings(test_strings[i]);
        if (result != NULL) {
            printf("Input: '%s' -> Output: '%s'\n", test_strings[i], result);
            free(result);
        } else {
            printf("Input: '%s' -> Error processing\n", test_strings[i]);
        }
    }

    return 0;
}