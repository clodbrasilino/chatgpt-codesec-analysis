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
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_pos = 0;
    size_t search_pos = 0;
    regmatch_t match;

    while (search_pos < input_len) {
        int match_result = regexec(&regex, input + search_pos, 1, &match, 0);
        
        if (match_result == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result + result_pos, input + search_pos);
            result_pos += input_len - search_pos;
            break;
        } else if (match_result == 0) {
            if (match.rm_so > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_pos, input + search_pos, match.rm_so);
                result_pos += match.rm_so;
            }
            search_pos += match.rm_eo;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "abcDEFghiJKL",
        "NoLowercase",
        "123abc456def789",
        "MixedCaseABCdefGHI",
        "",
        "alllowercase",
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