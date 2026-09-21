#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t result_idx = 0;
    const char *ptr = input;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = len - (size_t)(ptr - input);
            if (result_idx + remaining_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, ptr, remaining_len);
                result_idx += remaining_len;
            }
            break;
        }

        if (match.rm_so >= 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (copy_len > 0 && result_idx + copy_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, ptr, copy_len);
                result_idx += copy_len;
            }
        }

        ptr += match.rm_eo;
        if ((size_t)(ptr - input) > len) {
            break;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test = "Hello, World! 123 @#$%";
    char *cleaned = remove_non_alnum(test);
    
    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }
    
    return 0;
}